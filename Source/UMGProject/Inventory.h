// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "UniformGridPanel.h"
#include "UniformGridSlot.h"
#include "SlateBrush.h"
#include "SlateTypes.h"
#include "SlateColor.h"
#include "ItemSlotButton.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class UMGPROJECT_API UInventory : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void PostInitProperties() override;
	void NativeConstruct();

	// ������ ���� ����
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CreateItemSlot();

	// ��ư �̹���(��Ÿ��) ���� �� ��ȯ
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FButtonStyle SetStyle(UTexture2D* GetImage);

	// ������ ���� Ŭ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> ItemSlot;

	// ������ ���� �̹���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UTexture2D* SlotImage;

	// ������ ���� �÷�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FLinearColor SlotColor;

	// �ִ� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int SlotSize;

	// ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int ColumnLenth;

protected:
	// ���� �� ������ ������ �����ϴ� �迭
	UPROPERTY()
	TArray<UUserWidget*> ItemSlotList;

	// ������ ������ UI Grid�� �߰�
	void AddGridSlot(UUniformGridSlot* GridSlot);

	// ������ ���� ��� ���� ���� ��Ű�� �Լ�
	void IncrementSlotMatrix();

	// ������ ���Ե��� ������ UniformGird
	UPROPERTY()
	UUniformGridPanel* ItemGrid;

private:
	// ��� ��
	int Column;
	int Row;
};
