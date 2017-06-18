// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "ItemInfo.h"
#include "EquipItemButton.h"
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

	UPROPERTY()
	UEquipItemButton* WeaponSlot;

protected:

	void SetSlot();
	
};