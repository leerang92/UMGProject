// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "ItemInfo.h"
#include "UIEquipment.h"
#include "BaseItem.h"
#include "UserWidget.h"
#include "ItemManager.generated.h"

/**
 * 
 */
UCLASS()
class UMGPROJECT_API UItemManager : public UObject
{
	GENERATED_BODY()
	
public:

	void Initialize(APawn* pOwnerPawn);

	// ������ ����
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	void GetItem(FItemInfo Item);

	void EquipItem(FItemInfo GetItem);

	void SetWeapon(FItemInfo GetItem);

	UPROPERTY(BlueprintReadWrite, Category = "Item Manager")
	bool IsInventory;

	UPROPERTY(BlueprintReadWrite, Category = "Item Manager")
	bool IsEquipment;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* InventoryRef;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* EquipmentRef;

	UPROPERTY()
	ABaseItem* WeaponItem;

protected:
	// �����۵��� �����ϴ� �迭
	TArray<FItemInfo> InventoryList;

	FEquipItemInfo EquipItemInfo;

	UPROPERTY()
	APawn* OwnerPawn;

	void MinusItem(FItemInfo& GetItem);

public:

	// �κ��丮 ������ ��ȯ
	FORCEINLINE int GetInventorySize() const { return InventoryList.Num(); }

	FORCEINLINE int GetItemAmount(int Index) const { return InventoryList.Num() > Index ? InventoryList[Index].Amount : NULL; }

	// ������ ���� ��ȯ
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	FORCEINLINE FItemInfo GetItemInfo(int Index) { return InventoryList[Index]; }

	// ������ �̹��� ��ȯ
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	inline UTexture2D* GetItemImage(int Index) const { return InventoryList.Num() > Index ? InventoryList[Index].Image : nullptr; }

	FORCEINLINE FEquipItemInfo GetEquipItemInfo() { return EquipItemInfo; }


};
