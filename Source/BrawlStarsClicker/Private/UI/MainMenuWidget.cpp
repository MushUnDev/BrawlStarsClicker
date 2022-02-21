// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWidget.h"
#include "UI/SettingsWidget.h"
#include "UI/DataWidget.h"

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (BP_SettingsWidget)
	{
		BP_SettingsWidget->OnSettings.AddUObject(this, &UMainMenuWidget::OnSettings);
	}
}

void UMainMenuWidget::OnSettings(bool VisibilityFlag)
{
	if (!BP_DataWidget) return;

	BP_DataWidget->SetVisibility(VisibilityFlag ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}