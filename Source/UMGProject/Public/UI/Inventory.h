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
	virtual void NativeConstruct() override;

	// 아이템 슬롯 생성
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CreateItemSlot();

	void RenewSlot();

protected:
	// 버튼 이미지(스타일) 설정 후 반환
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FButtonStyle SetStyle(UTexture2D* GetImage);

	// 아이템 슬롯을 UI Grid에 추가
	void AddGridSlot(UUniformGridSlot* GridSlot);

	void BindButtonEvent(UItemSlot* Slot);

	// 아이템 슬롯 행과 열을 증가 시키는 함수
	void IncrementSlotMatrix();

public:
	// 아이템 슬롯 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> ItemSlot;

	// 아이템 슬롯 이미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UTexture2D* SlotImage;

	// 이미지 사이즈
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FVector2D ImageSize;

	// 아이템 슬롯 컬러
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FLinearColor SlotColor;

	// 최대 슬롯 갯수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int SlotSize;

	// 행의 갯수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int ColumnLenth;

protected:
	// 생성 된 아이템 슬롯을 저장하는 배열
	UPROPERTY()
	TArray<class UItemSlot*> ItemSlotList;

	// 아이템 슬롯들을 배정할 UniformGird
	UPROPERTY()
	class UUniformGridPanel* ItemGrid;

private:
	// 행과 열
	int Column;
	int Row;
};
