// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "ItemSlot.h"

void UItemSlot::NativeConstruct()
{
	//UE_LOG(LogClass, Warning, TEXT("Constructor!!"));
	//if (ButtonTest)
	//ButtonTest->OnClicked.AddDynamic(this, &UItemSlot::ShowText);
}

void UItemSlot::SetButtonStyle(const FButtonStyle& InStyle, const int& Amount)
{
	if (Slot_Button) {
		Slot_Button->SetStyle(InStyle);
		if(Amount > 0)
			Amount_Text->SetText(FText::AsNumber(Amount));
	}
}
