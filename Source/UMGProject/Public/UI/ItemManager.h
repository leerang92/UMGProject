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

	UItemManager();

	void Initialize(APawn* pOwnerPawn);

	// ������ ����
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	void AddItem(FItemInfo Item);

	// ������ ����
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	void SetEquipItem(FItemInfo GetItem);

	// ������ ���� ��ȯ
	int GetItemAmount(int Index) const;

	// ������ �̹��� ��ȯ
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	UTexture2D* GetItemImage(int Index) const;

	UFUNCTION(BlueprintCallable, Category = "Tooltip")
	void CreateTooltip(const FItemInfo& Item);

	UFUNCTION(BlueprintCallable, Category = "Tooltip")
	void Remove();

	// ���� �κ��丮 UI ���� ����
	UPROPERTY(BlueprintReadOnly, Category = "Item Manager")
	bool IsInventory;

	// ���� ��� UI ���� ����
	UPROPERTY(BlueprintReadOnly, Category = "Item Manager")
	bool IsEquipment;

	// �κ��丮 UI ���۷���
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* InventoryRef;

	// ��� UI ���۷���
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* EquipmentRef;

	UPROPERTY()
	UUserWidget* TooltipRef;

protected:
	// �����۵��� �����ϴ� �迭
	TArray<FItemInfo> InventoryList;

	// ���� ������ ����
	FEquipItemInfo EquipItemInfo;

	// ���� Ŭ����
	UPROPERTY()
	ABaseItem* WeaponItem;

	// ���â�� ǥ���� ���� Ŭ����
	UPROPERTY()
	ABaseItem* EquipWeaponItem;

	// �÷��̾� ��
	UPROPERTY()
	APawn* OwnerPawn;

	UPROPERTY()
	class UUserWidget* Tooltip;

	// ���� ������ ����
	void SetWeapon(FItemInfo GetItem);

	// ������ ���� �谨
	void MinusItemAmount(const FItemInfo& GetItem);

	// UI ����
	void RenewUI();
	void EquipmentRenew();

	// ��� UI�� ǥ���� ĳ���� ����
	void SetEquipUICharacter(FItemInfo GetItem);

public:

	// �κ��丮 ������ ��ȯ
	FORCEINLINE int GetInventorySize() const { return InventoryList.Num(); }

	// ������ ���� ��ȯ
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	FORCEINLINE FItemInfo GetItemInfo(int Index) { return InventoryList[Index]; }

	// ���� ������ ���� ��ȯ
	FORCEINLINE FEquipItemInfo GetEquipItemInfo()  { return EquipItemInfo; }
};
