// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "TextBlock.h"
#include "ItemInfo.h"
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
	void SetButtonStyle(const FButtonStyle& InStyle);

	// ������ ���� ����
	void SetItemInfo(const FItemInfo& GetItem);

	// Ŭ��
	UFUNCTION(BlueprintCallable, Category = "Slot Click")
	void OnClick();

protected:
	// ��ư Ŭ����
	UPROPERTY()
	UButton* Slot_Button;
	// �ؽ�Ʈ Ŭ����
	UPROPERTY()
	UTextBlock* Amount_Text;

	// ���� Ŭ�� ��� Ÿ�̸��ڵ�
	FTimerHandle ClickTimer;
	
	// ���� ������ �־�� �� ������ ����
	FItemInfo ItemInfo;
	
	// ���� Ŭ�� ����
	bool IsDoubleClick;

	int ClickCount;

	// ���� Ŭ�� �� ������ �Լ�
	void OnDoubleClick();

	// Ŭ�� ��� �ð��� ������ Ŭ�� ī��Ʈ�� �ʱ�ȭ�� �Լ�
	void ClickReset();
};
