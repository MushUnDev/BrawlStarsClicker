// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuBrawler/MenuBrawlerController.h"
#include "UI/DataWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ClickerData/ClickerGameInstance.h"
#include "ClickerData/BrawlersPrimaryDataAsset.h"

DEFINE_LOG_CATEGORY_STATIC(MenuBrawlerController, All, All)

AMenuBrawlerController::AMenuBrawlerController()
{
	if (GetWorld())
	{
		GameInstance = Cast<UClickerGameInstance>(GetWorld()->GetGameInstance());
	}
}

bool AMenuBrawlerController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
{
	switch (Type)
	{
	case ETouchType::Type::Began:
		return TouchBegan();
		break;
	case ETouchType::Type::Ended:
		if (IsPressed) return TouchEnded();
		break;
	default:
		break;
	}

	return Super::InputTouch(Handle, Type, TouchLocation, Force, DeviceTimestamp, TouchpadIndex);
}

bool AMenuBrawlerController::TouchBegan()
{
	IsPressed = true;

	if (!GetWorld() || !GameInstance) return false;

	GameInstance->AddCoins();

	return IsPressed;
}

bool AMenuBrawlerController::TouchEnded()
{
	if (!GetWorld()) return false;

	IsPressed = false;

	return !IsPressed;
}
