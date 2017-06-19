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
	void AddItem(FItemInfo Item);

	// 아이템 장착
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	void SetEquipItem(FItemInfo GetItem);

	// 아이템 개수 반환
	int GetItemAmount(int Index) const;

	// 아이템 이미지 반환
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	UTexture2D* GetItemImage(int Index) const;

	// 현재 인벤토리 UI 생성 여부
	UPROPERTY(BlueprintReadOnly, Category = "Item Manager")
	bool IsInventory;

	// 현재 장비 UI 생성 여부
	UPROPERTY(BlueprintReadOnly, Category = "Item Manager")
	bool IsEquipment;

	// 인벤토리 UI 레퍼런스
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* InventoryRef;

	// 장비 UI 레퍼런스
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* EquipmentRef;

protected:
	// 아이템들을 저장하는 배열
	TArray<FItemInfo> InventoryList;

	// 장착 아이템 정보
	FEquipItemInfo EquipItemInfo;

	// 무기 클래스
	UPROPERTY()
	ABaseItem* WeaponItem;

	// 장비창에 표시할 무기 클래스
	UPROPERTY()
	ABaseItem* EquipWeaponItem;

	// 플레이어 폰
	UPROPERTY()
	APawn* OwnerPawn;

	// 무기 아이템 장착
	void SetWeapon(FItemInfo GetItem);

	// 아이템 갯수 삭감
	void MinusItemAmount(const FItemInfo& GetItem);

	// UI 갱신
	void RenewUI();

	// 장비 UI에 표시할 캐릭터 세팅
	void SetEquipUICharacter(FItemInfo GetItem);

public:

	// 인벤토리 사이즈 반환
	FORCEINLINE int GetInventorySize() const { return InventoryList.Num(); }

	// 아이템 정보 반환
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	FORCEINLINE FItemInfo GetItemInfo(int Index) { return InventoryList[Index]; }

	// 장착 아이템 정보 반환
	FORCEINLINE FEquipItemInfo GetEquipItemInfo()  { return EquipItemInfo; }
};
