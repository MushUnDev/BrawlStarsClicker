// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ClickerCoreData.h"
#include "BrawlersPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class BRAWLSTARSCLICKER_API UBrawlersPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	FBrawlerPropereties* GetBrawlerInfoByEnum(BrawlersEnum Brawler) { return &BrawlersInfo[Brawler]; }
	const FTransform& GetBrawlerTransform() const { return BrawlerTransform; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ClickerBrawlersData")
		TMap<BrawlersEnum, FBrawlerPropereties> BrawlersInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ClickerBrawlersData")
		FTransform BrawlerTransform;
};
