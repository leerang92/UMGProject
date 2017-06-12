// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "ItemManager.h"


void UItemManager::GetItem(FItemInfo Item)
{
	// ������ ������ 0�� �� 1���� ����
	if (Item.Amount <= 0) { Item.Amount = 1; }

	if (InventoryList.Num() > 0)
	{
		bool IsAddItem = false;
		for (int32 i = 0; i < InventoryList.Num(); ++i) 
		{
			// ���� �������� �ִ��� �˻��� ���� �� ������ ����
			if (InventoryList[i].Name == Item.Name) {
				InventoryList[i].Amount++;
				IsAddItem = true;
				break;
			}
		}
		// ���� �������� ���� �� ���� ����
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
