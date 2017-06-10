// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "TextBlock.h"
#include "ItemSlotButton.h"
#include "ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class UMGPROJECT_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	UButton* Slot_Button;

	UPROPERTY()
	UTextBlock* Amount_Text;

	void SetButtonStyle(const FButtonStyle& InStyle, const int& Amount);
};
