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
			// Uniform Gird�� Slot UI(Widget) Ŭ���� �߰�
			AddGridSlot(ItemGrid->AddChildToUniformGrid(ItemWidget[i]));

			UItemSlot* Slot = Cast<UItemSlot>(ItemWidget[i]);
			AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
			if (Slot && Character)
			{
				// ��ư�� ������ �̹��� �׸���
				UTexture2D* ItemImage = Character->Item->GetItemImage(i);
				const int Amount = Character->Item->GetItemAmount(i);
				Slot->SetButtonStyle(SetStyle(ItemImage), Amount);

				// ������ ���Կ� ������ ���� ����
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
			// Uniform Gird�� Slot UI(Widget) Ŭ���� �߰�
			class UUserWidget* Widget = ItemWidget[i];
			ItemGrid->RemoveChild(Widget);
			AddGridSlot(ItemGrid->AddChildToUniformGrid(Widget));

			UItemSlot* Slot = Cast<UItemSlot>(ItemWidget[i]);
			AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
			if (Slot && Character)
			{
				// ��ư�� ������ �̹��� �׸���
				UTexture2D* ItemImage = Character->Item->GetItemImage(i);
				const int Amount = Character->Item->GetItemAmount(i);
				Slot->SetButtonStyle(SetStyle(ItemImage), Amount);

				// ������ ���Կ� ������ ���� ����
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

void UInventory::IncrementSlotMatrix()
{
	Column++;
	if (Column >= ColumnLenth)
	{
		Column = 0;
		Row++;
	}
}
