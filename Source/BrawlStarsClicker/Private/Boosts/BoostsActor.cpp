// Fill out your copyright notice in the Description page of Project Settings.


#include "Boosts/BoostsActor.h"
#include "Boosts/AutoClickComponent.h"
#include "Boosts/RandomGemClickComponent.h"
#include "ClickerData/ClickerGameInstance.h"
#include "ClickerCoreData.h"
#include "Boosts/RandomBigClickComponent.h"
#include "ClickerData/BrawlersPrimaryDataAsset.h"

DEFINE_LOG_CATEGORY_STATIC(LogBoostsActor, All, All)

ABoostsActor::ABoostsActor()
{
	PrimaryActorTick.bCanEverTick = false;

	AutoClickComponent = CreateDefaultSubobject<UAutoClickComponent>("AutoClickComponent");
	AutoClickComponent->OnAutoClickAdd.AddUObject(this, &ABoostsActor::OnCoinsChanged);

	RandomGemClickComponent = CreateDefaultSubobject<URandomGemClickComponent>("RandomGemClickComponent");

	RandomBigClickComponent = CreateDefaultSubobject<URandomBigClickComponent>("RandomBigClickComponent");
}

void ABoostsActor::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UClickerGameInstance>(GetGameInstance());
	if (!GameInstance) return;

	auto AvailableBoostsArray = GameInstance->GetAvailableBoosts();

	if (AutoClickComponent)
	{
		AutoClickComponent->SetAutoclickAvailable(GameInstance->IsBoostAvailable(BoostsEnum::AutoClick)); 
		AutoClickComponent->SetMoneyToAdd(GameInstance->GetCurrentMoney());
		AutoClickComponent->SetSumToAdd(GameInstance->GetCurrentClickerCoefficient());
		AutoClickComponent->StartAutoClick();
	}

	if (RandomGemClickComponent)
	{
		RandomGemClickComponent->SetRandomGemClickAvailable(GameInstance->IsBoostAvailable(BoostsEnum::RandomGemClick));
		RandomGemClickComponent->SetMoneyToAdd(GameInstance->GetCurrentGems());
	}

	if (RandomBigClickComponent)
	{
		RandomBigClickComponent->SetRandomBigClickAvailable(GameInstance->IsBoostAvailable(BoostsEnum::BigRandomClick));
		RandomBigClickComponent->SetRandomBigClickCoefficient(GameInstance->GetCurrentClickerCoefficient());
		RandomBigClickComponent->SetMoneyToAdd(GameInstance->GetCurrentMoney());
	}

	GameInstance->OnBrawlerChanged.AddUObject(this, &ABoostsActor::OnBrawlerChanged);
	GameInstance->OnCoinsCountChanged.AddUObject(this, &ABoostsActor::ForRandomGemOrBigCoinsSum);
	GameInstance->OnBuyingBoost.AddUObject(this, &ABoostsActor::OnBuyingBoost);
}

void ABoostsActor::OnCoinsChanged()
{
	GameInstance->OnCoinsCountChanged.Broadcast(GameInstance->GetCurrentMoney());
}

void ABoostsActor::ForRandomGemOrBigCoinsSum(FMoneyStruct* Money)
{
	if (RandomGemClickComponent->RandomAddGem()) GameInstance->OnGemsCountChanged.Broadcast(GameInstance->GetCurrentGems());
	if (RandomBigClickComponent->RandomAddCoins()) GameInstance->OnCoinsCountChanged.Broadcast(GameInstance->GetCurrentMoney());
}

void ABoostsActor::OnBrawlerChanged(BrawlersEnum BrawlerEnum)
{
	AutoClickComponent->SetSumToAdd((GameInstance->GetBrawlersInfoData())->GetBrawlerInfoByEnum(BrawlerEnum)->ClickCoefficient);
	RandomBigClickComponent->SetRandomBigClickCoefficient((GameInstance->GetBrawlersInfoData())->GetBrawlerInfoByEnum(BrawlerEnum)->ClickCoefficient);
}

void ABoostsActor::OnBuyingBoost(BoostsEnum Boost)
{
	switch (Boost)
	{
	case BoostsEnum::AutoClick:
		AutoClickComponent->SetAutoclickAvailable(GameInstance->IsBoostAvailable(BoostsEnum::AutoClick));
		AutoClickComponent->StartAutoClick();
		break;

	case BoostsEnum::BigRandomClick:
		RandomBigClickComponent->SetRandomBigClickAvailable(GameInstance->IsBoostAvailable(BoostsEnum::BigRandomClick));
		break;

	case BoostsEnum::RandomGemClick:
		RandomGemClickComponent->SetRandomGemClickAvailable(GameInstance->IsBoostAvailable(BoostsEnum::RandomGemClick));
		break;
	default:
		return;
	}
}