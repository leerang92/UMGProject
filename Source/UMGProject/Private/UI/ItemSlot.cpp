// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "UMGProjectCharacter.h"
#include "SlateBrush.h"
#include "ItemSlot.h"


void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	World = GetWorld();
	ClickCount = 0;

	// ��� �̹��� ����
	FSlateBrush Brush;
	Brush.TintColor = FLinearColor(0.079f, 0.085f, 0.068f, 1.0f);
	Brush.SetResourceObject(BackgroundImage);
	Background->SetBrush(Brush);
}

void UItemSlot::SetButtonStyle(const FButtonStyle& InStyle, const int GetAmount)
{
	if (Slot_Button) {
		Slot_Button->SetStyle(InStyle);
		if (GetAmount > 0)
			Amount_Text->SetText(FText::AsNumber(GetAmount));
		else
			Amount_Text->SetText(FText::GetEmpty());
	}
}

void UItemSlot::SetItemInfo(FItemInfo GetItem)
{
	ItemInfo = GetItem;
}

void UItemSlot::OnClick()
{
	if (World) {
		// �ѹ� Ŭ��
		ClickCount++;
		// ���� Ŭ��
		if (ClickCount >= 2)
		{
			OnDoubleClick();
			ClickReset();
		}
		else if (ClickCount == 1)
		{
			// ���� Ŭ�������� ���ð�
			World->GetTimerManager().SetTimer(ClickTimerHandle, this, &UItemSlot::ClickReset, 0.3f, false);
		}
	}
}

void UItemSlot::ShowTooltip()
{
	AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
	if (Character)
	{
		Tooltip = CreateWidget<UUserWidget>(Character->GetWorld(), Character->Tolltip);
		Tooltip->AddToViewport();

		if (Tooltip)
		{
			float LocationX;
			float LocationY;

			APlayerController* MyController = Character->GetWorld()->GetFirstPlayerController();
			MyController->GetMousePosition(LocationX, LocationY);
			const FVector2D MousePosition = FVector2D(LocationX, LocationY);
			Tooltip->SetPositionInViewport(MousePosition);
		}
	}
}

void UItemSlot::RemoveTooltip()
{
	if (Tooltip)
	{
		Tooltip->RemoveFromViewport();
	}
}

void UItemSlot::OnDoubleClick()
{
	if (ItemInfo.Amount <= 0)
		return;

	AUMGProjectCharacter* Character = Cast<AUMGProjectCharacter>(GetOwningPlayerPawn());
	if (Character && ItemInfo.BPClass != nullptr)
	{
		Character->Item->SetEquipItem(ItemInfo);
		ItemInfo.Amount--;
	}
}

void UItemSlot::ClickReset()
{
	World->GetTimerManager().ClearTimer(ClickTimerHandle);
	ClickCount = 0;
}
