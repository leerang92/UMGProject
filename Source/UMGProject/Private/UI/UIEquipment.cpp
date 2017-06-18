// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "UMGProjectCharacter.h"
#include "UIEquipment.h"


void UUIEquipment::NativeConstruct()
{
	Super::NativeConstruct();

	SetSlot();

}

void UUIEquipment::SetSlot()
{
	AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
	if (Character)
	{
		WeaponSlot->SetButton(Character->Item->GetEquipItemInfo().Weapon);
	}
}
