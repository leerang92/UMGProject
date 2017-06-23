// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "Inventory.h"
#include "BaseItem.h"
#include "UMGProjectCharacter.h"
#include "ItemManager.h"

UItemManager::UItemManager()
{
	UE_LOG(LogClass, Warning, TEXT("Constructor"));
}

void UItemManager::Initialize(APawn* pOwnerPawn)
{
	OwnerPawn = pOwnerPawn;
}

void UItemManager::AddItem(FItemInfo Item)
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
	} 
	else {
		InventoryList.Add(Item);
	}

	// UI ����
	RenewUI();
}

void UItemManager::SetEquipItem(FItemInfo GetItem)
{
	MinusItemAmount(GetItem);

	// ������ Ÿ�Կ� �´� �������� ����
	const EItemType::Type Type = GetItem.ItemType;
	switch (Type)
	{
	case EItemType::Head:
		break;
	case EItemType::Weapon: 
		SetWeapon(GetItem); 
		break;
	}
	RenewUI();
}

void UItemManager::SetWeapon(FItemInfo GetItem)
{
	AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(OwnerPawn);
	UWorld* World = Character->GetWorld();

	if (Character && World)
	{
		// ���� ������ ����
		if (WeaponItem)
		{
			AddItem(WeaponItem->ItemInfo);
			WeaponItem->Destroy();
		}
		
		// ������ ���� �� ���Ͽ� �����ϸ�, ��� �迭�� ������ ���� ����.
		WeaponItem = World->SpawnActor<ABaseItem>((UClass*)GetItem.BPClass->GeneratedClass);
		if (WeaponItem)
		{
			WeaponItem->Mesh->AttachTo(Character->GetMesh(), TEXT("WeaponSocket"));
			EquipItemInfo.Weapon = GetItem;

			SetEquipUICharacter(GetItem);
		}
	}
}

void UItemManager::MinusItemAmount(const FItemInfo & GetItem)
{
	// �κ��丮���� ���Ǵ� ������ ���� �谨 �� 0�� �� ������ ����Ʈ���� ����.
	for (int32 i = 0; i < InventoryList.Num(); ++i)
	{
		if (InventoryList[i].Name == GetItem.Name)
		{
			InventoryList[i].Amount--;
			if(InventoryList[i].Amount <= 0) { InventoryList.RemoveAt(i); }
		}
	}
}

void UItemManager::RenewUI()
{
	// �κ��丮 �������� �� ����
	if (IsInventory)
	{
		UInventory* Inven = Cast<UInventory>(InventoryRef);
		if (Inven)
		{
			Inven->RenewSlot();
		}
	}
	// ��� UI �������� �� ����
	if (IsEquipment)
	{
		UUIEquipment* EquipUI = Cast<UUIEquipment>(EquipmentRef);
		if (EquipUI)
		{
			EquipUI->SetSlot();
		}
	}
}

void UItemManager::SetEquipUICharacter(FItemInfo GetItem)
{
	AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(OwnerPawn);
	UWorld* World = Character->GetWorld();

	if (Character && World)
	{
		// ���� ������ ����
		if (EquipWeaponItem)
		{
			EquipWeaponItem->Destroy();
		}

		EquipWeaponItem = World->SpawnActor<ABaseItem>((UClass*)GetItem.BPClass->GeneratedClass);
		if (EquipWeaponItem)
		{
			EquipWeaponItem->Mesh->AttachTo(Character->EquipCharacter->Mesh, TEXT("WeaponSocket"));
		}
	}
}

UTexture2D * UItemManager::GetItemImage(int Index) const
{
	return InventoryList.Num() > Index ? InventoryList[Index].Image : nullptr;
}

int UItemManager::GetItemAmount(int Index) const
{
	return InventoryList.Num() > Index ? InventoryList[Index].Amount : NULL;
}
