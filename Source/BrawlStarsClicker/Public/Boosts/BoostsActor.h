// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoostsActor.generated.h"

class UAutoClickComponent;
class UClickerGameInstance;
class URandomGemClickComponent;
struct FMoneyStruct;
class URandomBigClickComponent;
struct FBrawlerPropereties;
enum class BoostsEnum : uint8;
enum class BrawlersEnum : uint8;

UCLASS()
class BRAWLSTARSCLICKER_API ABoostsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoostsActor();

protected:
	virtual void BeginPlay() override;

private:
	UAutoClickComponent* AutoClickComponent;
	URandomGemClickComponent* RandomGemClickComponent;
	URandomBigClickComponent* RandomBigClickComponent;

	UClickerGameInstance* GameInstance;

	void OnCoinsChanged();

	void ForRandomGemOrBigCoinsSum(FMoneyStruct* Money);

	void OnBrawlerChanged(BrawlersEnum Brawler);

	void OnBuyingBoost(BoostsEnum Boost);
};
