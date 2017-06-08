// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "Inventory.h"

UUserWidget* UInventory::CreateItemSlot(UUniformGridPanel* UniformGrid)
{
	if (ItemSlot)
	{
		/*for (int32 i = 0; i < SlotSize; ++i)
		{*/
			ItemWidget = CreateWidget<UUserWidget>(GetWorld(), ItemSlot);
			if (ItemWidget)
			{
				AddGridSlot(UniformGrid->AddChildToUniformGrid(ItemWidget));
				UE_LOG(LogClass, Warning, TEXT("Succes Create!"));
			}
		/*}*/
		
	}
	return ItemWidget;
}

void UInventory::AddGridSlot(UUniformGridSlot* GridSlot)
{
	GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	GridSlot->SetColumn(Column);
	GridSlot->SetRow(Row);
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
