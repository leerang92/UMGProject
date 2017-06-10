// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "UMGProjectCharacter.h"
#include "ItemSlot.h"
#include "Inventory.h"

void UInventory::PostInitProperties()
{
	Super::PostInitProperties();

	//CreateItemSlot();
}

void UInventory::NativeConstruct()
{
	CreateItemSlot();
}

void UInventory::CreateItemSlot()
{
	if (ItemSlot)
	{
		for (int32 i = 0; i < SlotSize; ++i)
		{
			UUserWidget* ItemWidget = CreateWidget<UUserWidget>(GetWorld(), ItemSlot);
			if (ItemWidget)
			{
				//ItemSlotList.Add(ItemWidget);
				// Uniform Gird�� �߰�
				AddGridSlot(ItemGrid->AddChildToUniformGrid(ItemWidget));
				UItemSlot* Slot = Cast<UItemSlot>(ItemWidget);
				if (Slot)
				{
					AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
					if (Character)
					{
						UTexture2D* ItemImage = Character->Item->GetItemImage(i);
						int ItemAmount = Character->Item->GetItemAmount(i);
						Slot->SetButtonStyle(SetStyle(ItemImage), ItemAmount);
					}	
				}
			}
		}
	}
}

FButtonStyle UInventory::SetStyle(UTexture2D* GetImage)
{
	FSlateBrush SBrush;
	// Slate Brush ����
	SBrush.ImageSize = FVector2D(32.0f, 32.0f);
	SBrush.TintColor = FLinearColor(0.079f, 0.085f, 0.068f, 1.0f);

	// ���� �̹����� Null�� �ƴϸ� ���� �̹����� ����
	UTexture2D* SetItemImage = GetImage != nullptr ? GetImage : SlotImage;
	SBrush.SetResourceObject(SetItemImage);
		
	// ��ư ��Ÿ���� Slate Brush�� ����
	FButtonStyle BtnStyle;
	BtnStyle.SetNormal(SBrush);

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
