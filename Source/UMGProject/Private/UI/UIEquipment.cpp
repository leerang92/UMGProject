// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "UMGProjectCharacter.h"
#include "ItemInfo.h"
#include "UIEquipment.h"


void UUIEquipment::NativeConstruct()
{
	Super::NativeConstruct();

	SetSlot();
}

void UUIEquipment::ShowTooltip(const FItemInfo& Item)
{
	if (Item.Image == nullptr)
		return;

	AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
	if (Character)
	{
		Tooltip = CreateWidget<UUserWidget>(Character->GetWorld(), Character->Tolltip);
		Tooltip->AddToViewport();

		if (Tooltip)
		{
			UUITooltip* TooltipClass = Cast<UUITooltip>(Tooltip);
			TooltipClass->GetItemInfo(Item);
			
			FVector2D MousePosition = FVector2D::ZeroVector;

			APlayerController* Controller = Character->GetWorld()->GetFirstPlayerController();
			Controller->GetMousePosition(MousePosition.X, MousePosition.Y);

			FAnchors Anchors(0,0,1,1);		
			Tooltip->SetAnchorsInViewport(Anchors);
			Tooltip->SetPositionInViewport(MousePosition);
		}
	}
}

void UUIEquipment::RemoveTooltip()
{
	if (Tooltip)
	{
		Tooltip->RemoveFromViewport();
	}
}

FSlateBrush UUIEquipment::SetBackgroundStyle()
{
	FSlateBrush Brush;
	Brush.TintColor = FLinearColor(0.079f, 0.085f, 0.068f, 1.0f);
	Brush.ImageSize = FVector2D(80.0f, 80.0f);
	Brush.SetResourceObject(BackgroundImage);

	return Brush;
}

void UUIEquipment::SetSlot()
{
	AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
	if (Character)
	{
		//WeaponBackground->SetBrush(SetBackgroundStyle());
		const FEquipItemInfo EquipItemInfo = Character->Item->GetEquipItemInfo();

		WeaponSlot->SetButton(EquipItemInfo.Weapon);
	}
}
