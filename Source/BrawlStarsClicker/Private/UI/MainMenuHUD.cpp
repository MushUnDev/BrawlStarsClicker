// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuHUD.h"
#include "Blueprint/UserWidget.h"

void AMainMenuHUD::BeginPlay()
{
	if (MainMenuWidgetClass)
	{
		const auto MainMenuWidget = CreateWidget(GetWorld(), MainMenuWidgetClass);
		MainMenuWidget->AddToViewport();
	}
	
}