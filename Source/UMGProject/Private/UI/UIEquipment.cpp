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
		const FEquipItemInfo ItemInfo = Character->Item->GetEquipItemInfo();

		if (ItemInfo.Weapon.Image != nullptr) 
			WeaponSlot->SetButton(ItemInfo.Weapon);
		else
			WeaponSlot->SetEmptyButton(BackgroundImage);
	}
}
