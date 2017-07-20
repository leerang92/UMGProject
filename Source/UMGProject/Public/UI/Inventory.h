// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "UniformGridPanel.h"
#include "UniformGridSlot.h"
#include "SlateBrush.h"
#include "SlateTypes.h"
#include "SlateColor.h"
#include "ItemSlot.h"
#include "UMGProjectCharacter.h"
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

	// ������ ���� ����
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CreateItemSlot();

	void RenewSlot();

	void SetOwnerPawn(APawn* OwnerPawn);

	FORCEINLINE class AUMGProjectCharacter* GetOwnerPawn() const { return MyPawn; }

protected:
	// ��ư �̹���(��Ÿ��) ���� �� ��ȯ
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FButtonStyle SetStyle(UTexture2D* GetImage);

	// ������ ������ UI Grid�� �߰�
	void AddGridSlot(UUniformGridSlot* GridSlot);

	void BindButtonEvent(UItemSlot* Slot);

	// ������ ���� ��� ���� ���� ��Ű�� �Լ�
	void IncrementSlotMatrix();

public:
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
	UPROPERTY()
	class AUMGProjectCharacter* MyPawn;

	// ���� �� ������ ������ �����ϴ� �迭
	UPROPERTY()
	TArray<class UItemSlot*> ItemSlotList;

	// ������ ���Ե��� ������ UniformGird
	UPROPERTY()
	class UUniformGridPanel* ItemGrid;

private:
	// ��� ��
	int Column;
	int Row;
};
