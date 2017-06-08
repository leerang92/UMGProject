// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class UMGPROJECT_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Slot")
	void GetButton(UButton* GetButton);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	UButton* Button;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	TSubclassOf<UButton> Button1;
};
