// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "Image.h"
#include "TextBlock.h"
#include "ItemInfo.h"
#include "BaseItem.h"
#include "TimerManager.h"
#include "ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class UMGPROJECT_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	// ��ư ��Ÿ�� ����
	void SetButtonStyle(const FButtonStyle& InStyle, const int GetAmount);

	// ������ ���� ����
	void SetItemInfo(FItemInfo GetItem);

	// Ŭ��
	UFUNCTION(BlueprintCallable, Category = "Slot Click")
	void OnClick();

	void HoveredTest();

	UFUNCTION(BlueprintCallable, Category = "Tooltip")
	void ShowTooltip();
	UFUNCTION(BlueprintCallable, Category = "Tooltip")
	void RemoveTooltip();

	UPROPERTY(EditAnywhere)
	UTexture2D* BackgroundImage;

	// ��ư Ŭ����
	UPROPERTY()
	UButton* Slot_Button;

	// ���� ������ �־�� �� ������ ����
	UPROPERTY(BlueprintReadOnly, Category = "Item Info")
		FItemInfo ItemInfo;

protected:
	UPROPERTY()
	UUserWidget* Tooltip;

	// �ؽ�Ʈ Ŭ����
	UPROPERTY()
	UTextBlock* Amount_Text;

	// ��� �̹���
	UPROPERTY()
	UImage* Background;

	UPROPERTY()
	UWorld* World;

	// ���� Ŭ�� ��� Ÿ�̸��ڵ�
	FTimerHandle ClickTimerHandle;
	


	// Ŭ�� Ƚ��
	int ClickCount;

	// ���� Ŭ�� �� ������ �Լ�
	void OnDoubleClick();

	// Ŭ�� ��� �ð��� ������ Ŭ�� ī��Ʈ�� �ʱ�ȭ�� �Լ�
	void ClickReset();
};
