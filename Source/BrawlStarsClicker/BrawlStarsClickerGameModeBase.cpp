// Copyright Epic Games, Inc. All Rights Reserved.


#include "BrawlStarsClickerGameModeBase.h"
#include "MenuBrawler/MenuBrawler.h"
#include "UI/MainMenuHUD.h"
#include "MenuBrawler/MenuBrawlerController.h"
#include "Boosts/BoostsActor.h"

ABrawlStarsClickerGameModeBase::ABrawlStarsClickerGameModeBase()
{
	DefaultPawnClass = AMenuBrawler::StaticClass();
	HUDClass = AMainMenuHUD::StaticClass();
	PlayerControllerClass = AMenuBrawlerController::StaticClass();

	
	if (GetWorld())
	{
		GetWorld()->SpawnActor(ABoostsActor::StaticClass());
	}
}
