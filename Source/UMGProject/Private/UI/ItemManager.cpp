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
	} 
	else {
		InventoryList.Add(Item);
	}

	// UI 갱신
	RenewUI();

}

void UItemManager::SetEquipItem(FItemInfo GetItem)
{
	MinusItemAmount(GetItem);

	// 아이템 타입에 맞는 슬롯으로 설정
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
		// 이전 아이템 삭제
		if (WeaponItem)
		{
			AddItem(WeaponItem->ItemInfo);
			WeaponItem->Destroy();
		}
		
		// 아이템 생성 후 소켓에 부착하며, 장비 배열에 아이템 정보 저장.
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
	// 인벤토리에서 사용되는 아이템 개수 삭감 및 0일 시 아이템 리스트에서 삭제.
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
	// 인벤토리 열려있을 시 갱신
	if (InventoryRef && InventoryRef->IsInViewport())
	{
		UInventory* Inven = Cast<UInventory>(InventoryRef);
		if (Inven)
		{
			Inven->RenewSlot();
		}
	}
	// 장비 UI 열려있을 시 갱신
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
		// 이전 아이템 삭제
		if (EquipWeaponItem)
		{
			EquipWeaponItem->Destroy();
		}

		// 장착 아이템을 장비UI 캐릭터의 부착
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
