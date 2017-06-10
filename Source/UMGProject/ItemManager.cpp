// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "ItemManager.h"


void UItemManager::GetItem(FItemInfo Item)
{
	if (InventoryList.Num() > 0)
	{
		bool IsAddItem = false;
		for (int32 i = 0; i < InventoryList.Num(); ++i) {
			if (InventoryList[i].Name == Item.Name) {
				InventoryList[i].Amount++;
				IsAddItem = true;
				break;
			}
		}
		if (!IsAddItem) { InventoryList.Add(Item); }
	}
	else {
		if (Item.Amount <= 0) {
			Item.Amount = 1;
		}
		InventoryList.Add(Item);
	}
	
}

UTexture2D* UItemManager::GetItemImage(int Index) const
{
	if (InventoryList.Num() > Index)
		return InventoryList[Index].Image;
	else
		return nullptr;
}

int32 UItemManager::GetItemAmount(int Index) const
{
	if (InventoryList.Num() > Index)
		return InventoryList[Index].Amount;
	else
		return 0;
}
