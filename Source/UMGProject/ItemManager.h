// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "ItemInfo.h"
#include "ItemManager.generated.h"

/**
 * 
 */
UCLASS()
class UMGPROJECT_API UItemManager : public UObject
{
	GENERATED_BODY()
	
public:

	// 아이템 습득
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	void GetItem(FItemInfo Item);

	// 아이템 이미지 반환
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	UTexture2D* GetItemImage(int Index) const;

	// 아이템 정보 반환
	UFUNCTION(BlueprintCallable, Category = "Item Manager")
	FItemInfo GetItemInfo(int Index);

	// 인벤토리 사이즈 반환
	int GetInventorySize() const;
	 
protected:
	// 아이템들을 저장하는 배열
	TArray<FItemInfo> InventoryList;
};
