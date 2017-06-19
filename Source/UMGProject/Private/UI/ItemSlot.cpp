// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "UMGProjectCharacter.h"
#include "SlateBrush.h"
#include "ItemSlot.h"


void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	World = GetWorld();
	ClickCount = 0;

	// 배경 이미지 설정
	FSlateBrush Brush;
	Brush.TintColor = FLinearColor(0.079f, 0.085f, 0.068f, 1.0f);
	Brush.SetResourceObject(BackgroundImage);
	Background->SetBrush(Brush);
}

void UItemSlot::SetButtonStyle(const FButtonStyle& InStyle, const int GetAmount)
{
	if (Slot_Button) {
		Slot_Button->SetStyle(InStyle);
		if (GetAmount > 0)
			Amount_Text->SetText(FText::AsNumber(GetAmount));
		else
			Amount_Text->SetText(FText::GetEmpty());
	}
}

void UItemSlot::SetItemInfo(FItemInfo GetItem)
{
	ItemInfo = GetItem;
}

void UItemSlot::OnClick()
{
	if (World) {
		// 한번 클릭
		ClickCount++;
		if (ClickCount == 1)
		{
			// 더블 클릭까지의 대기시간
			World->GetTimerManager().SetTimer(ClickTimerHandle, this, &UItemSlot::ClickReset, 0.3f, false);
		}
		// 더블 클릭
		else if (ClickCount >= 2)
		{
			OnDoubleClick();
			ClickReset();
		}
	}
}

void UItemSlot::ShowItemInfo()
{
	UE_LOG(LogClass, Warning, TEXT("Hovered"));
	//AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
	//UUserWidget* InfoWidget = CreateWidget<UUserWidget>(Character->GetWorld(), Character->ItemInfo);
	//InfoWidget->AddToViewport();
	//InfoWidget->SetPositionInViewport(FVector2D(0,0));
}

void UItemSlot::OnDoubleClick()
{
	if (ItemInfo.Amount <= 0)
		return;

	AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
	if (Character && ItemInfo.BPClass != nullptr)
	{
		Character->Item->SetEquipItem(ItemInfo);
		ItemInfo.Amount--;
	}
}

void UItemSlot::ClickReset()
{
	World->GetTimerManager().ClearTimer(ClickTimerHandle);
	ClickCount = 0;
}
