// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "ItemSlot.h"

void UItemSlot::NativeConstruct()
{
	IsDoubleClick = false;
	ClickCount = 0;

	if (Slot_Button)
	{
		Slot_Button->OnClicked.AddDynamic(this, &UItemSlot::OnClick);
	}
}

void UItemSlot::SetButtonStyle(const FButtonStyle& InStyle)
{
	if (Slot_Button) {
		Slot_Button->SetStyle(InStyle);
	}
}

void UItemSlot::SetItemInfo(const FItemInfo& GetItem)
{
	ItemInfo = GetItem;
	if (ItemInfo.Amount > 0)
		Amount_Text->SetText(FText::AsNumber(ItemInfo.Amount));
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
	UE_LOG(LogClass, Warning, TEXT("%s"), *ItemInfo.Name.ToString());
}

void UItemSlot::ClickReset()
{
	ClickCount = 0;
}
