// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "ItemInfo.h"
#include "Image.h"
#include "Button.h"
#include "TextBlock.h"
#include "UITooltip.generated.h"

/**
 * 
 */
UCLASS()
class UMGPROJECT_API UUITooltip : public UUserWidget
{
	GENERATED_BODY()

public:
	void GetItemInfo(const FItemInfo& GetItem);
protected:
	UPROPERTY()
	UImage* ItemImage;
	
	UPROPERTY()
	UTextBlock* ItemName;
};
