// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "UMGProjectCharacter.h"
#include "ItemSlot.h"
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
		UE_LOG(LogClass, Warning, TEXT("No Item Slot Class, Please Select Item Slot UI Class"));
		return;
	}
	for (int32 i = 0; i < SlotSize; ++i)
	{
		ItemWidget.Add(CreateWidget<UUserWidget>(GetWorld(), ItemSlot));
		if (ItemWidget[i])
		{
			// Uniform Gird에 Slot UI(Widget) 클래스 추가
			AddGridSlot(ItemGrid->AddChildToUniformGrid(ItemWidget[i]));

			UItemSlot* Slot = Cast<UItemSlot>(ItemWidget[i]);
			AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
			if (Slot && Character)
			{
				// 버튼의 아이템 이미지 그리기
				UTexture2D* ItemImage = Character->Item->GetItemImage(i);
				const int Amount = Character->Item->GetItemAmount(i);
				Slot->SetButtonStyle(SetStyle(ItemImage), Amount);

				// 아이템 슬롯에 아이템 정보 저장
				if (Character->Item->GetInventorySize() > i)
				{
					Slot->SetItemInfo(Character->Item->GetItemInfo(i));
				}
			}
		}
	}
}

void UInventory::AddSlot()
{
	Column = 0;
	Row = 0;
	for (int32 i = 0; i < SlotSize; ++i)
	{
		if (ItemWidget[i])
		{
			// Uniform Gird에 Slot UI(Widget) 클래스 추가
			class UUserWidget* Widget = ItemWidget[i];
			ItemGrid->RemoveChild(Widget);
			AddGridSlot(ItemGrid->AddChildToUniformGrid(Widget));

			UItemSlot* Slot = Cast<UItemSlot>(ItemWidget[i]);
			AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
			if (Slot && Character)
			{
				// 버튼의 아이템 이미지 그리기
				UTexture2D* ItemImage = Character->Item->GetItemImage(i);
				const int Amount = Character->Item->GetItemAmount(i);
				Slot->SetButtonStyle(SetStyle(ItemImage), Amount);

				// 아이템 슬롯에 아이템 정보 저장
				if (Character->Item->GetInventorySize() > i)
				{
					Slot->SetItemInfo(Character->Item->GetItemInfo(i));

				}
			}
		}
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

void UInventory::IncrementSlotMatrix()
{
	Column++;
	if (Column >= ColumnLenth)
	{
		Column = 0;
		Row++;
	}
}
