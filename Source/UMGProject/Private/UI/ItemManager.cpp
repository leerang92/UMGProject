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
	UWorld* World = MyPawn->GetWorld();

	if (MyPawn && World)
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
			WeaponItem->Mesh->AttachTo(MyPawn->GetMesh(), TEXT("WeaponSocket"));
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
	if (InventoryRef && InventoryRef->IsInViewport())
	{
		UInventory* Inven = Cast<UInventory>(InventoryRef);
		if (Inven)
		{
			Inven->RenewSlot();
		}
	}
	// ��� UI �������� �� ����
	if (EquipmentRef && EquipmentRef->IsInViewport())
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
	UWorld* World = MyPawn->GetWorld();

	if (MyPawn && World)
	{
		// ���� ������ ����
		if (EquipWeaponItem)
		{
			EquipWeaponItem->Destroy();
		}

		// ���� �������� ���UI ĳ������ ����
		EquipWeaponItem = World->SpawnActor<ABaseItem>((UClass*)GetItem.BPClass->GeneratedClass);
		if (EquipWeaponItem)
		{
			EquipWeaponItem->Mesh->AttachTo(MyPawn->EquipCharacter->Mesh, TEXT("WeaponSocket"));
		}
	}
}

UTexture2D * UItemManager::GetItemImage(int Index) const
{
	return InventoryList.Num() > Index ? InventoryList[Index].Image : nullptr;
}

void UItemManager::CreateTooltip(const FItemInfo & Item)
{
	if (Item.Image == nullptr)
		return;
	if (Tooltip)
		Tooltip->RemoveFromViewport();

	if (MyPawn)
	{
		Tooltip = CreateWidget<UUserWidget>(MyPawn->GetWorld(), MyPawn->Tolltip);
		
		if (Tooltip) 
		{
			UUITooltip* TC = Cast<UUITooltip>(Tooltip);
			TC->GetItemInfo(Item);

			FVector2D MousePosition = FVector2D::ZeroVector;
			APlayerController* Controller = MyPawn->GetWorld()->GetFirstPlayerController();
			Controller->GetMousePosition(MousePosition.X, MousePosition.Y);
			Tooltip->SetPositionInViewport(MousePosition);

			Tooltip->AddToViewport();
		}
	}
}

void UItemManager::RemoveTooltip()
{
	if (Tooltip)
		Tooltip->RemoveFromViewport();
}

void UItemManager::SetOwnerPawn(APawn * OwnerPawn)
{
	if (OwnerPawn && MyPawn != OwnerPawn)
	{
		MyPawn = Cast<AUMGProjectCharacter>(OwnerPawn);
	}
}

int UItemManager::GetItemAmount(int Index) const
{
	return InventoryList.Num() > Index ? InventoryList[Index].Amount : NULL;
}
