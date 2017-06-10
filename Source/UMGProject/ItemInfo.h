// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "ItemInfo.generated.h"

UENUM(BlueprintType)
namespace EItemType
{
	enum Type
	{
		Head,
		Body,
		Weapon,
	};
}

USTRUCT(BlueprintType)
struct FItemInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	int Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	TEnumAsByte<enum EItemType::Type> ItemType;
};
