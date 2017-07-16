// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "ItemInfo.h"
#include "Image.h"
#include "SlateBrush.h"
#include "ItemButton.h"
#include "UITooltip.h"
#include "UIEquipment.generated.h"

/**
 * 
 */
UCLASS()
class UMGPROJECT_API UUIEquipment : public UUserWidget
{
	GENERATED_BODY()
	 
public:

	virtual void NativeConstruct() override;

	void SetSlot();

	UFUNCTION(BlueprintCallable, Category = "Tooltip")
	void ShowTooltip(const FItemInfo& Item);
	
	UFUNCTION(BlueprintCallable, Category = "Tooltip")
	void RemoveTooltip();

	FSlateBrush SetBackgroundStyle();

	UPROPERTY(BlueprintReadOnly, Category = "Item Slot")
	UItemButton* WeaponSlot;
	UPROPERTY(BlueprintReadOnly, Category = "Item Slot")
		UUserWidget* Tooltip;
protected:
	

	UPROPERTY(EditAnywhere)
	UTexture2D* BackgroundImage;

	UPROPERTY()
	UImage* WeaponBackground;

	
	
	
};
