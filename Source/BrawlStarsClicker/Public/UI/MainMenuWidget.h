// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class USettingsWidget;
class UDataWidget;

UCLASS()
class BRAWLSTARSCLICKER_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
		USettingsWidget* BP_SettingsWidget;

	UPROPERTY(meta = (BindWidget))
		UDataWidget* BP_DataWidget;

	virtual void NativeOnInitialized() override;

private:
	void OnSettings(bool Visibility);
};
