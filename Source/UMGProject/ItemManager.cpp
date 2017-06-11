// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "ItemManager.h"


void UItemManager::GetItem(FItemInfo Item)
{
	// 아이템 갯수가 0일 시 1개로 저장
	if (Item.Amount <= 0) { Item.Amount = 1; }

	if (InventoryList.Num() > 0)
	{
		bool IsAddItem = false;
		for (int32 i = 0; i < InventoryList.Num(); ++i) 
		{
			// 같은 아이템이 있는지 검색후 있을 시 갯수만 증가
			if (InventoryList[i].Name == Item.Name) {
				InventoryList[i].Amount++;
				IsAddItem = true;
				break;
			}
		}
		// 같은 아이템이 없을 시 새로 저장
		if (!IsAddItem) { InventoryList.Add(Item); }
	} else {
		InventoryList.Add(Item);
	}
	
}

UTexture2D* UItemManager::GetItemImage(int Index) const
{
	return InventoryList.Num() > Index ? InventoryList[Index].Image : nullptr;
}

FItemInfo UItemManager::GetItemInfo(int Index)
{
	return InventoryList[Index];
}

int UItemManager::GetInventorySize() const
{
	return InventoryList.Num();
}
