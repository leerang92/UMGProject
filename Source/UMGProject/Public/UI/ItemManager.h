// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "ItemInfo.h"
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

	// ������ ����
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	void GetItem(FItemInfo Item);

	// ������ �̹��� ��ȯ
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	UTexture2D* GetItemImage(int Index) const;

	// ������ ���� ��ȯ
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	FItemInfo GetItemInfo(int Index);

	// �κ��丮 ������ ��ȯ
	int GetInventorySize() const;

	UPROPERTY(BlueprintReadWrite, Category = "Item Manager")
	bool IsInventory;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* InventoryRef;
	 
protected:
	// �����۵��� �����ϴ� �迭
	TArray<FItemInfo> InventoryList;
};
