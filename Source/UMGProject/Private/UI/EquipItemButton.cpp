// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "SlateBrush.h"
#include "EquipItemButton.h"

void UEquipItemButton::SetButton(FItemInfo GetItem)
{
	ItemInfo = GetItem;

	FSlateBrush Brush;

	Brush.SetResourceObject(GetItem.Image);

	FButtonStyle BtnStyle;
	BtnStyle.SetNormal(Brush);

	Brush.TintColor = FLinearColor(0.079f, 0.085f, 0.068f, 1.0f);
	BtnStyle.SetHovered(Brush);
	BtnStyle.SetPressed(Brush);

	this->SetStyle(BtnStyle);
}
