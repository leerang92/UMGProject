// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "UniformGridPanel.h"
#include "UniformGridSlot.h"
#include "SlateBrush.h"
#include "SlateTypes.h"
#include "SlateColor.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class UMGPROJECT_API UInventory : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// ������ ���� ����
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CreateItemSlot();

	void RenewSlot();

	// ������ ���� Ŭ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> ItemSlot;

	// ������ ���� �̹���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UTexture2D* SlotImage;

	// �̹��� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FVector2D ImageSize;

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
	TArray<class UItemSlot*> ItemSlotList;

	// ������ ���Ե��� ������ UniformGird
	UPROPERTY()
	UUniformGridPanel* ItemGrid;

	// ��ư �̹���(��Ÿ��) ���� �� ��ȯ
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FButtonStyle SetStyle(UTexture2D* GetImage);

	// ������ ������ UI Grid�� �߰�
	void AddGridSlot(UUniformGridSlot* GridSlot);

	void BindButtonEvent(UItemSlot* Slot);

	// ������ ���� ��� ���� ���� ��Ű�� �Լ�
	void IncrementSlotMatrix();

private:
	// ��� ��
	int Column;
	int Row;
};
