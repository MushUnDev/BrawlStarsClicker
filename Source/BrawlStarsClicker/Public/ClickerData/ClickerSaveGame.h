// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ClickerCoreData.h"
#include "ClickerSaveGame.generated.h"

UCLASS()
class BRAWLSTARSCLICKER_API UClickerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = "ClickerData")
		FMoneyStruct Coins;

	UPROPERTY(VisibleAnywhere, Category = "ClickerData")
		FMoneyStruct Gems;

	UPROPERTY(VisibleAnywhere, Category = "ClickerData")
		BrawlersEnum CurrentBrawler;

	UPROPERTY(VisibleAnywhere, Category = "ClickerData")
		TArray<BrawlersEnum> AvailableBrawlers;

	UPROPERTY(VisibleAnywhere, Category = "ClickerData")
		TArray<BoostsEnum> AvailableBoosts;

	UPROPERTY(VisibleAnywhere, Category = "ClickerData")
		BrawlersSkins CurrentSkin;

	UPROPERTY(VisibleAnywhere, Category = "ClickerData")
		TArray<BrawlersSkins> AvailableSkins;


	UClickerSaveGame();

};
