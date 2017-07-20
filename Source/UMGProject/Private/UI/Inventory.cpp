// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "Inventory.h"

void UInventory::NativeConstruct()
{
	Super::NativeConstruct();

	CreateItemSlot();
}

void UInventory::CreateItemSlot()
{
	if (!ItemSlot)
	{
		UE_LOG(LogClass, Warning, TEXT("아이템 슬롯 클래스가 없습니다."));
		return;
	}

	for (int32 i = 0; i < SlotSize; ++i)
	{
		// 슬롯 생성 후 배열에 저장 
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), ItemSlot);
		if (Widget)
		{
			// Uniform Gird에 Slot UI(Widget) 클래스 추가
			AddGridSlot(ItemGrid->AddChildToUniformGrid(Widget));

			// 아이템 슬롯 설정
			ItemSlotList.Add(Cast<UItemSlot>(Widget));
			AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
			if (ItemSlotList[i] && Character)
			{
				// 버튼의 아이템 이미지 그리기
				UTexture2D* ItemImage = Character->Item->GetItemImage(i);
				const int Amount = Character->Item->GetItemAmount(i);
				// 슬롯 스타일 설정
				ItemSlotList[i]->SetButtonStyle(SetStyle(ItemImage), Amount);

				// 아이템 슬롯에 아이템 정보 저장
				if (Character->Item->GetInventorySize() > i)
				{
					ItemSlotList[i]->SetItemInfo(Character->Item->GetItemInfo(i));
					BindButtonEvent(ItemSlotList[i]);
				}
			}
		}
	}
}

void UInventory::RenewSlot()
{
	Column = 0;
	Row = 0;
	for (int32 i = 0; i < SlotSize; ++i)
	{
		AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
		if (ItemSlotList[i] && Character)
		{
			// 버튼의 아이템 이미지 그리기
			UTexture2D* ItemImage = Character->Item->GetItemImage(i);
			const int Amount = Character->Item->GetItemAmount(i);
			ItemSlotList[i]->SetButtonStyle(SetStyle(ItemImage), Amount);

			// 아이템 슬롯에 아이템 정보 저장
			if (Character->Item->GetInventorySize() > i)
			{
				ItemSlotList[i]->SetItemInfo(Character->Item->GetItemInfo(i));
				BindButtonEvent(ItemSlotList[i]);
			}
		}
	}
}

void UInventory::SetOwnerPawn(APawn * OwnerPawn)
{
	if (OwnerPawn && MyPawn != OwnerPawn)
	{
		MyPawn = Cast<AUMGProjectCharacter>(OwnerPawn);
	}
}

FButtonStyle UInventory::SetStyle(UTexture2D* GetImage)
{
	FSlateBrush SBrush;
	
	/* 노말 버튼 스타일 설정 */
	SBrush.ImageSize = ImageSize;
	if(!GetImage)
		SBrush.TintColor = FLinearColor(0.079f, 0.085f, 0.068f, 1.0f);

	// 받은 이미지가 Null이 아니면 슬롯 이미지로 설정
	UTexture2D* SetItemImage = GetImage != nullptr ? GetImage : SlotImage;
	SBrush.SetResourceObject(SetItemImage);
		
	// 버튼 스타일을 Slate Brush로 설정
	FButtonStyle BtnStyle;
	BtnStyle.SetNormal(SBrush);

	/* 커서를 올렸을 때와 클릭시의 버튼 스타일 설정 */
	SBrush.TintColor = FLinearColor(0.079f, 0.085f, 0.068f, 0.4f);
	BtnStyle.SetHovered(SBrush);
	BtnStyle.SetPressed(SBrush);

	return BtnStyle;
}

void UInventory::AddGridSlot(UUniformGridSlot* GridSlot)
{
	// UniformGrid 설정
	GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	GridSlot->SetColumn(Column);
	GridSlot->SetRow(Row);

	// 행렬을 증가 시킨다
	IncrementSlotMatrix();
}

void UInventory::BindButtonEvent(UItemSlot* Slot)
{
	Slot->Slot_Button->OnClicked.AddDynamic(Slot, &UItemSlot::OnClick);
	Slot->Slot_Button->OnHovered.AddDynamic(Slot, &UItemSlot::HoveredTest);
}

void UInventory::IncrementSlotMatrix()
{
	Column++;
	if (Column >= ColumnLenth)
	{
		Column = 0;
		Row++;
	}
}
