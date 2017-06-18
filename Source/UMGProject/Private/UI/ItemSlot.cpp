// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "UMGProjectCharacter.h"
#include "SlateBrush.h"
#include "ItemSlot.h"

void UItemSlot::NativeConstruct()
{
	IsDoubleClick = false;
	ClickCount = 0;

	if (Slot_Button)
	{
		Slot_Button->OnClicked.AddDynamic(this, &UItemSlot::OnClick);
	}

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
	ClickCount++;
	UWorld* World = GetWorld();
	if (World) {
		// 한번 클릭
		if (ClickCount == 0)
		{
			// 더블 클릭까지의 대기시간
			World->GetTimerManager().SetTimer(ClickTimer, this, &UItemSlot::ClickReset, 0.5f, false);
		}
		// 더블 클릭
		else if (ClickCount > 1)
		{
			World->GetTimerManager().ClearTimer(ClickTimer);
			OnDoubleClick();
			ClickCount = 0;
		}
	}
}

void UItemSlot::OnDoubleClick()
{
	AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
	if (Character && ItemInfo.BPClass != nullptr)
	{
		ItemInfo.Amount--;
		Character->Item->EquipItem(ItemInfo);
		
		//if (ItemInfo.Amount <= 0) { 
		//	FMemory::Memset(ItemInfo, 0);
		//}
	}
}

void UItemSlot::ClickReset()
{
	ClickCount = 0;
}
