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

	// 버튼 스타일 설정
	void SetButtonStyle(const FButtonStyle& InStyle, const int GetAmount);

	// 아이템 정보 저장
	void SetItemInfo(FItemInfo GetItem);

	// 클릭
	UFUNCTION(BlueprintCallable, Category = "Slot Click")
	void OnClick();

	void HoveredTest();

	UFUNCTION(BlueprintCallable, Category = "Tooltip")
	void ShowTooltip();
	UFUNCTION(BlueprintCallable, Category = "Tooltip")
	void RemoveTooltip();

	UPROPERTY(EditAnywhere)
	UTexture2D* BackgroundImage;

	// 버튼 클래스
	UPROPERTY()
	UButton* Slot_Button;

	// 현재 가지고 있어야 할 아이템 정보
	UPROPERTY(BlueprintReadOnly, Category = "Item Info")
		FItemInfo ItemInfo;

protected:
	UPROPERTY()
	UUserWidget* Tooltip;

	// 텍스트 클래스
	UPROPERTY()
	UTextBlock* Amount_Text;

	// 배경 이미지
	UPROPERTY()
	UImage* Background;

	UPROPERTY()
	UWorld* World;

	// 더블 클릭 대기 타이머핸들
	FTimerHandle ClickTimerHandle;
	


	// 클릭 횟수
	int ClickCount;

	// 더블 클릭 시 실행할 함수
	void OnDoubleClick();

	// 클릭 대기 시간이 지나면 클릭 카운트를 초기화할 함수
	void ClickReset();
};
