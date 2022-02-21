// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickerData/ClickerGameInstance.h"

void UClickerGameInstance::AddCoins(int32 CoinsToAdd)
{
	ClikerData.Coins += CoinsToAdd;

	OnCoinsCountChanged.Broadcast(ClikerData.Coins);
}

void UClickerGameInstance::AddGems(int32 GemsToAdd)
{
	ClikerData.Gems += GemsToAdd;
}

