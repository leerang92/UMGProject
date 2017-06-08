// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "Inventory.h"

UUserWidget* UInventory::CreateItemSlot(UUniformGridPanel* UniformGrid)
{
	if (ItemSlot)
	{
		/*for (int32 i = 0; i < SlotSize; ++i)
		{*/
			ItemWidget = CreateWidget<UUserWidget>(GetWorld(), ItemSlot);
			if (ItemWidget)
			{
				//UItemSlot* Item = Cast<UItemSlot>(ItemWidget);

				//FSlateBrush SBrush;
				//SBrush.ImageSize = FVector2D(32.0f, 32.0f);
				//SBrush.TintColor = FLinearColor(0.079f, 0.085f, 0.068f, 1.0f);

				//FButtonStyle BtnStyle;
				//BtnStyle.SetNormal(SBrush);

				//Item->Button->SetStyle(BtnStyle);
				AddGridSlot(UniformGrid->AddChildToUniformGrid(ItemWidget));
				UE_LOG(LogClass, Warning, TEXT("Succes Create!"));
			}
		/*}*/
		
	}
	return ItemWidget;
}

FButtonStyle UInventory::SetStyle()
{
	FSlateBrush SBrush;
	SBrush.ImageSize = FVector2D(32.0f, 32.0f);
	SBrush.TintColor = FLinearColor(0.079f, 0.085f, 0.068f, 0.2f);

	FButtonStyle BtnStyle;
	BtnStyle.SetNormal(SBrush);
	//FSlateBrush SetBrush{
	//	(SlateBrushDefs::DefaultImageSize, SlateBrushDefs::DefaultImageSize)
	//	, ESlateBrushDrawType::Image
	//	, 0.0f
	//	, FLinearColor::White
	//	, FLinearColor::White
	//	, ESlateBrushTileType::NoTile
	//	, ESlateBrushMirrorType::NoMirror
	//	, ESlateBrushImageType::NoImage
	//	, nullptr
	//	, NAME_None
	//	, false
	//	, false
	//	, ForceInit };
	//SetBrush.ImageSize = FVector2D(32.0f, 32.0f);
	//BtnStyle.SetNormal(SetBrush);
	return BtnStyle;
}

void UInventory::AddGridSlot(UUniformGridSlot* GridSlot)
{
	GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	GridSlot->SetColumn(Column);
	GridSlot->SetRow(Row);
	IncrementSlotMatrix();
}

void UInventory::IncrementSlotMatrix()
{
	Column++;
	if (Column >= ColumnLenth)
	{
		Column = 0;
		Row++;
	}
}
