// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class BRAWLSTARSCLICKER_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<UUserWidget> MainMenuWidgetClass;

};
