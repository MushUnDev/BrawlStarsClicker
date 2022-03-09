// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ShopWidget.h"
#include "Components/Button.h"
#include "Components/Overlay.h"

void UShopWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ShopButton)
	{
		ShopButton->OnClicked.AddDynamic(this, &UShopWidget::Shop);
	}
}

void UShopWidget::Shop()
{
	if (!ShopOverlay) return;

	ShopVisibility = !ShopVisibility;

	ShopOverlay->SetVisibility(ShopVisibility ? ESlateVisibility::Visible :
		ESlateVisibility::Hidden);

	ShopVisibility ? GetOwningPlayer()->SetInputMode(FInputModeUIOnly()) : GetOwningPlayer()->SetInputMode(FInputModeGameOnly());

	OnShop.Broadcast(!ShopVisibility);
}