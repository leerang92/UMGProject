// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Button.h"
#include "ItemSlotButton.generated.h"

/**
 * 
 */
UCLASS()
class UMGPROJECT_API UItemSlotButton : public UButton
{
	GENERATED_BODY()
	
public:
	
	void SetButtonStyle(const FButtonStyle& InStyle)
	{
		SetStyle(InStyle);
	}
	
};
