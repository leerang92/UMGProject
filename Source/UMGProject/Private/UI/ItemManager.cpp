// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "Inventory.h"
#include "BaseItem.h"
#include "UMGProjectCharacter.h"
#include "ItemManager.h"

void UItemManager::Initialize(APawn* pOwnerPawn)
{
	OwnerPawn = pOwnerPawn;
}

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

	if (IsInventory)
	{
		UInventory* Inven = Cast<UInventory>(InventoryRef);
		if (Inven)
		{
			Inven->AddSlot();
		}
	}

}

void UItemManager::EquipItem(FItemInfo GetItem)
{
	MinusItem(GetItem);
	const EItemType::Type Type = GetItem.ItemType;
	switch (Type)
	{
	case EItemType::Head:
		break;
	case EItemType::Weapon: 
		SetWeapon(GetItem); 
		break;
	}

	UInventory* Inven = Cast<UInventory>(InventoryRef);
	if (Inven)
	{
		Inven->AddSlot();
	}
}

void UItemManager::SetWeapon(FItemInfo GetItem)
{
	AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(OwnerPawn);
	if (Character)
	{
		UWorld* World = Character->GetWorld();
		if (World) {
			if (WeaponItem)
			{
				WeaponItem->Destroy();
			}
			
			WeaponItem = World->SpawnActor<ABaseItem>((UClass*)GetItem.BPClass->GeneratedClass);
			if (WeaponItem)
			{
				UUIEquipment* Equip = Cast<UUIEquipment>(EquipmentRef);
				WeaponItem->Mesh->AttachTo(Character->GetMesh(), TEXT("WeaponSocket"));

				if (Equip) { EquipItemInfo.Weapon = GetItem; }
			}
		}
	}
}

void UItemManager::MinusItem(FItemInfo & GetItem)
{
	for (int32 i = 0; i < InventoryList.Num(); ++i)
	{
		if (InventoryList[i].Name == GetItem.Name)
		{
			InventoryList[i].Amount--;
			if(InventoryList[i].Amount <= 0) { InventoryList.RemoveAt(i); }
		}
	}
}
