// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ClickerCoreData.h"
#include "BoostsPrimaryDataAsset.generated.h"

UCLASS()
class BRAWLSTARSCLICKER_API UBoostsPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	FBoostsPropereties* GetBoostInfoByEnum(BoostsEnum Boost) { return &BoostsInfo[Boost]; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ClickerBrawlersData")
		TMap<BoostsEnum, FBoostsPropereties> BoostsInfo;

};
