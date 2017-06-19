// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Button.h"
#include "ItemInfo.h"
#include "EquipItemButton.generated.h"

/**
 * 
 */
UCLASS()
class UMGPROJECT_API UEquipItemButton : public UButton
{
	GENERATED_BODY()
	
public:
	FItemInfo ItemInfo;

	// æ∆æ∆≈€ ΩΩ∑‘ º≥¡§
	void SetButton(FItemInfo GetItem);

	// ∫Û ΩΩ∑‘ º≥¡§
	void SetEmptyButton(UTexture* EmptyImage);
	
};
