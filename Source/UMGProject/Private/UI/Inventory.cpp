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
		UE_LOG(LogClass, Warning, TEXT("������ ���� Ŭ������ �����ϴ�."));
		return;
	}

	for (int32 i = 0; i < SlotSize; ++i)
	{
		// ���� ���� �� �迭�� ���� 
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), ItemSlot);
		if (Widget)
		{
			// Uniform Gird�� Slot UI(Widget) Ŭ���� �߰�
			AddGridSlot(ItemGrid->AddChildToUniformGrid(Widget));

			// ������ ���� ����
			ItemSlotList.Add(Cast<UItemSlot>(Widget));
			AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
			if (ItemSlotList[i] && Character)
			{
				// ��ư�� ������ �̹��� �׸���
				UTexture2D* ItemImage = Character->Item->GetItemImage(i);
				const int Amount = Character->Item->GetItemAmount(i);
				// ���� ��Ÿ�� ����
				ItemSlotList[i]->SetButtonStyle(SetStyle(ItemImage), Amount);

				// ������ ���Կ� ������ ���� ����
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
			// ��ư�� ������ �̹��� �׸���
			UTexture2D* ItemImage = Character->Item->GetItemImage(i);
			const int Amount = Character->Item->GetItemAmount(i);
			ItemSlotList[i]->SetButtonStyle(SetStyle(ItemImage), Amount);

			// ������ ���Կ� ������ ���� ����
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
	
	/* �븻 ��ư ��Ÿ�� ���� */
	SBrush.ImageSize = ImageSize;
	if(!GetImage)
		SBrush.TintColor = FLinearColor(0.079f, 0.085f, 0.068f, 1.0f);

	// ���� �̹����� Null�� �ƴϸ� ���� �̹����� ����
	UTexture2D* SetItemImage = GetImage != nullptr ? GetImage : SlotImage;
	SBrush.SetResourceObject(SetItemImage);
		
	// ��ư ��Ÿ���� Slate Brush�� ����
	FButtonStyle BtnStyle;
	BtnStyle.SetNormal(SBrush);

	/* Ŀ���� �÷��� ���� Ŭ������ ��ư ��Ÿ�� ���� */
	SBrush.TintColor = FLinearColor(0.079f, 0.085f, 0.068f, 0.4f);
	BtnStyle.SetHovered(SBrush);
	BtnStyle.SetPressed(SBrush);

	return BtnStyle;
}

void UInventory::AddGridSlot(UUniformGridSlot* GridSlot)
{
	// UniformGrid ����
	GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	GridSlot->SetColumn(Column);
	GridSlot->SetRow(Row);

	// ����� ���� ��Ų��
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
