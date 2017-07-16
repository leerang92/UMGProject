// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "SlateBrush.h"
#include "UITooltip.h"


void UUITooltip::GetItemInfo(const FItemInfo& GetItem)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(GetItem.Image);
	ItemImage->SetBrush(Brush);

	ItemName->SetText(FText::FromName(GetItem.Name));

}

