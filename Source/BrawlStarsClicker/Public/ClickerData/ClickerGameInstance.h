// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ClickerCoreData.h"
#include "ClickerGameInstance.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCoinsCountChangedSignature, FMoneyStruct*)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGemsCountChangedSignature, FMoneyStruct*)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBrawlerChangedSignature, BrawlersEnum)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuyingBoostSignature, BoostsEnum)
DECLARE_MULTICAST_DELEGATE(FOnGameLoadedSignature)

class UClickerSaveGame;
class UBrawlersPrimaryDataAsset;
class UBoostsPrimaryDataAsset;
class USaveGame;

UCLASS()
class BRAWLSTARSCLICKER_API UClickerGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FOnCoinsCountChangedSignature OnCoinsCountChanged;
	FOnGemsCountChangedSignature OnGemsCountChanged;
	FOnBrawlerChangedSignature OnBrawlerChanged;
	FOnGameLoadedSignature OnGameLoaded;
	FOnBuyingBoostSignature OnBuyingBoost;

	void AddCoins();
	void AddGems(int32 GemsToAdd);

	UBrawlersPrimaryDataAsset* GetBrawlersInfoData() { return BrawlersInfoData; }

	void SetCurrentBrawler(BrawlersEnum NewBrawler) { CurrentBrawler = NewBrawler; }

	BrawlersEnum* GetCurrentBrawler() { return &CurrentBrawler; }

	void AddAvailableBrawler(BrawlersEnum Brawler) { AvailableBrawlers.Add(Brawler); }

	bool IsBrawlerAvailable(BrawlersEnum Brawler) const { return AvailableBrawlers.Contains(Brawler); }

	bool IsBrawlerCurrent(BrawlersEnum Brawler) { return CurrentBrawler == Brawler; }

	AActor* GetCurrentBrawlerClass() { return CurrentBrawlerClass; }

	void SetCurrentBrawlerClass(AActor* NewBralwerClass) { CurrentBrawlerClass = NewBralwerClass; }


	FMoneyStruct* GetCurrentMoney() { return &Coins; }

	FMoneyStruct* GetCurrentGems() { return &Gems; }

	void SetClickerCoefficient(float NewCoefficient) { ClickCoefficient = NewCoefficient; }

	int32 GetCurrentClickerCoefficient() const { return ClickCoefficient; }


	const TArray<BoostsEnum>& GetAvailableBoosts() { return AvailableBoosts; }

	bool IsBoostAvailable(BoostsEnum Boost) const { return AvailableBoosts.Contains(Boost); }

	UBoostsPrimaryDataAsset* GetBoostsInfoData() { return BoostsInfoData; }

	void AddAvailableBoost(BoostsEnum Boost) { AvailableBoosts.Add(Boost); }


	virtual void OnStart() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ClickerData")
		UBrawlersPrimaryDataAsset* BrawlersInfoData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ClickerData")
		UBoostsPrimaryDataAsset* BoostsInfoData;

private:
	FMoneyStruct Coins;
	FMoneyStruct Gems;

	BrawlersEnum CurrentBrawler;
	AActor* CurrentBrawlerClass;
	TArray<BrawlersEnum> AvailableBrawlers;

	int32 ClickCoefficient;

	TArray<BoostsEnum> AvailableBoosts;

	FString SaveSlotName = TEXT("BaseClickerSlot");
	uint32 UserIndex = 0;

	void CreateAndSaveGame();
	void LoadGame();

};

