// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Button.h"
#include "ItemInfo.h"
#include "SlateBrush.h"
#include "ItemButton.generated.h"

/**
 * 
 */
UCLASS()
class UMGPROJECT_API UItemButton : public UButton
{
	GENERATED_BODY()
	
public:
	void SetButton(const FItemInfo& GetItem);

	UFUNCTION(BlueprintCallable, Category = "Item Info")
	FItemInfo GetItemInfo();

protected:
	UPROPERTY()
	UTexture* ItemImage;
	
	FItemInfo ItemInfo;
};
