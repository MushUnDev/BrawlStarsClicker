// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickerData/ClickerGameInstance.h"
#include "ClickerData/ClickerSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "BrawlStarsClicker/BrawlStarsClickerGameModeBase.h"
#include "ClickerData/BrawlersPrimaryDataAsset.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameInstance, All, All)

void UClickerGameInstance::OnStart()
{
	Super::OnStart();

	if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		CreateAndSaveGame();
	}
	
	LoadGame();
	OnGameLoaded.Broadcast();
}

void UClickerGameInstance::AddCoins()
{
	FMoneyStructUtils::Add(&Coins, ClickCoefficient);

	OnCoinsCountChanged.Broadcast(&Coins);
}

void UClickerGameInstance::AddGems(int32 GemsToAdd)
{
	FMoneyStructUtils::Add(&Gems, GemsToAdd);

	OnGemsCountChanged.Broadcast(&Gems);
}

void UClickerGameInstance::CreateAndSaveGame()
{
	auto ClickerSaveGame = Cast<UClickerSaveGame>(UGameplayStatics::CreateSaveGameObject(UClickerSaveGame::StaticClass()));
	if (!ClickerSaveGame) return;

	ClickerSaveGame->Coins = FMoneyStruct(0, 0, 0, 0);
	ClickerSaveGame->Gems = FMoneyStruct(0, 0, 0, 0);
	ClickerSaveGame->CurrentBrawler = BrawlersEnum::Shelly;
	ClickerSaveGame->AvailableBrawlers.Add(BrawlersEnum::Shelly);

	UGameplayStatics::SaveGameToSlot(ClickerSaveGame, SaveSlotName, UserIndex);
}

void UClickerGameInstance::LoadGame()
{
	auto ClickerSaveGame = Cast<UClickerSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	if (!ClickerSaveGame) return; 

	Coins = ClickerSaveGame->Coins;
	Gems = ClickerSaveGame->Gems;
	CurrentBrawler = ClickerSaveGame->CurrentBrawler;
	AvailableBrawlers = ClickerSaveGame->AvailableBrawlers;
	AvailableBoosts = ClickerSaveGame->AvailableBoosts;
	if (!BrawlersInfoData) return;
	ClickCoefficient = BrawlersInfoData->GetBrawlerInfoByEnum(CurrentBrawler)->ClickCoefficient;

	CurrentBrawlerClass = GetWorld()->SpawnActorAbsolute(BrawlersInfoData->GetBrawlerInfoByEnum(CurrentBrawler)->BrawlerClass, BrawlersInfoData->GetBrawlerTransform());

	OnBrawlerChanged.Broadcast(CurrentBrawler);
}

