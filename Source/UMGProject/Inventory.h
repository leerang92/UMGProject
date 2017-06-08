// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "UniformGridPanel.h"
#include "UniformGridSlot.h"
#include "SlateBrush.h"
#include "SlateTypes.h"
#include "SlateColor.h"
#include "ItemSlot.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class UMGPROJECT_API UInventory : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UUserWidget* CreateItemSlot(UUniformGridPanel* UniformGrid);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> ItemSlot;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FButtonStyle SetStyle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int SlotSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int ColumnLenth;

protected:
	UPROPERTY()
	class UUserWidget* ItemWidget;

	void AddGridSlot(UUniformGridSlot* GridSlot);
	void IncrementSlotMatrix();

private:
	int Column;
	int Row;
};
