// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SettingsWidget.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(SetLog, All, All)

void USettingsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (SettingsButton)
	{
		SettingsButton->OnClicked.AddDynamic(this, &USettingsWidget::Settings);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &USettingsWidget::Exit);
	}
}

void USettingsWidget::Settings()
{
	if (!SettingsItself && !GetWorld()) return;

	SettingsVisibility = !SettingsVisibility;

	SettingsItself->SetVisibility(SettingsVisibility ? ESlateVisibility::Visible 
		: ESlateVisibility::Hidden);

	SettingsVisibility ? GetOwningPlayer()->SetInputMode(FInputModeUIOnly()) : GetOwningPlayer()->SetInputMode(FInputModeGameOnly());

	OnSettings.Broadcast(!SettingsVisibility);
}

void USettingsWidget::Exit()
{
	if (!ExitButton && !GetWorld()) return;

	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}