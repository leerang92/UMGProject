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

	// 버튼 스타일 설정
	void SetButtonStyle(const FButtonStyle& InStyle);

	// 아이템 정보 저장
	void SetItemInfo(const FItemInfo& GetItem);

	// 클릭
	UFUNCTION(BlueprintCallable, Category = "Slot Click")
	void OnClick();

protected:
	// 버튼 클래스
	UPROPERTY()
	UButton* Slot_Button;
	// 텍스트 클래스
	UPROPERTY()
	UTextBlock* Amount_Text;

	// 더블 클릭 대기 타이머핸들
	FTimerHandle ClickTimer;
	
	// 현재 가지고 있어야 할 아이템 정보
	FItemInfo ItemInfo;
	
	// 더블 클릭 여부
	bool IsDoubleClick;

	int ClickCount;

	// 더블 클릭 시 실행할 함수
	void OnDoubleClick();

	// 클릭 대기 시간이 지나면 클릭 카운트를 초기화할 함수
	void ClickReset();
};
