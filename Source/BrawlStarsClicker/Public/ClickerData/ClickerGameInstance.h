// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ClickerCoreData.h"
#include "ClickerGameInstance.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCoinsCountChangedSignature, int32)

UCLASS()
class BRAWLSTARSCLICKER_API UClickerGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FOnCoinsCountChangedSignature OnCoinsCountChanged;

	int32 GetCoinsCount() const { return ClikerData.Coins; }
	int32 GetGemsCount() const { return ClikerData.Gems; }

	void AddCoins(int32 CoinsToAdd);
	void AddGems(int32 GemsToAdd);


protected:
	FClickerData ClikerData;
};
