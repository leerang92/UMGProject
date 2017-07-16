// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "UMGProjectCharacter.h"
#include "ItemButton.h"


void UItemButton::SetButton(const FItemInfo& GetItem)
{
	ItemInfo = GetItem;

	FSlateBrush Brush;
	if(GetItem.Image != nullptr)
		Brush.SetResourceObject(GetItem.Image);

	Brush.ImageSize = FVector2D(80.0f, 80.0f);

	FButtonStyle BtnStyle;
	BtnStyle.SetNormal(Brush);

	Brush.TintColor = FLinearColor(0.079f, 0.085f, 0.068f, 1.0f);
	BtnStyle.SetHovered(Brush);
	BtnStyle.SetPressed(Brush);

	this->SetStyle(BtnStyle);
}

FItemInfo UItemButton::GetItemInfo()
{
	return ItemInfo;
}
