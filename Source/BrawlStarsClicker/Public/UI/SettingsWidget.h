// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSettingsSignature, bool)

class UButton;
class UOverlay;

UCLASS()
class BRAWLSTARSCLICKER_API USettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnSettingsSignature OnSettings;
protected:
	UPROPERTY(meta = (BindWidget))
		UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
		UOverlay* SettingsItself;

	virtual void NativeOnInitialized() override;

private:
	bool SettingsVisibility = false;

	UFUNCTION()
		void Settings();

	UFUNCTION()
		void Exit();

};
