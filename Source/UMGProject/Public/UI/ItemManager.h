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

	// 아이템 습득
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
	// 아이템들을 저장하는 배열
	TArray<FItemInfo> InventoryList;

	FEquipItemInfo EquipItemInfo;

	UPROPERTY()
	APawn* OwnerPawn;

	void MinusItem(FItemInfo& GetItem);

public:

	// 인벤토리 사이즈 반환
	FORCEINLINE int GetInventorySize() const { return InventoryList.Num(); }

	FORCEINLINE int GetItemAmount(int Index) const { return InventoryList.Num() > Index ? InventoryList[Index].Amount : NULL; }

	// 아이템 정보 반환
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	FORCEINLINE FItemInfo GetItemInfo(int Index) { return InventoryList[Index]; }

	// 아이템 이미지 반환
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	inline UTexture2D* GetItemImage(int Index) const { return InventoryList.Num() > Index ? InventoryList[Index].Image : nullptr; }

	FORCEINLINE FEquipItemInfo GetEquipItemInfo() { return EquipItemInfo; }


};
