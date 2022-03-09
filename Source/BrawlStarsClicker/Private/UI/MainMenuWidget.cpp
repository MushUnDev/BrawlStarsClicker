// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWidget.h"
#include "UI/SettingsWidget.h"
#include "UI/DataWidget.h"
#include "UI/ShopWidget.h"
#include "UI/MinigamesWidget.h"

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (BP_SettingsWidget)
	{
		BP_SettingsWidget->OnSettings.AddUObject(this, &UMainMenuWidget::OnSettings);
	}

	if (BP_ShopWidget)
	{
		BP_ShopWidget->OnShop.AddUObject(this, &UMainMenuWidget::OnShop);
	}
}

void UMainMenuWidget::OnSettings(bool VisibilityFlag)
{
	if (!BP_DataWidget || !BP_ShopWidget) return;

	BP_DataWidget->SetVisibility(VisibilityFlag ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	BP_ShopWidget->SetVisibility(VisibilityFlag ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	BP_MinigamesWidget->SetVisibility(VisibilityFlag ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UMainMenuWidget::OnShop(bool VisibilityFlag)
{
	if (!BP_DataWidget || !BP_SettingsWidget) return;

	BP_DataWidget->SetVisibility(VisibilityFlag ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	BP_SettingsWidget->SetVisibility(VisibilityFlag ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	BP_MinigamesWidget->SetVisibility(VisibilityFlag ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}