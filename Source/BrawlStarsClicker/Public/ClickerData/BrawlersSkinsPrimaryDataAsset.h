// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ClickerCoreData.h"
#include "BrawlersSkinsPrimaryDataAsset.generated.h"

UCLASS()
class BRAWLSTARSCLICKER_API UBrawlersSkinsPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	FSkinPropereties* GetSkinProperitiesByEnum(BrawlersSkins BrawlerSkin) { return &SkinEnumToSkin[BrawlerSkin]; }
	BrawlersEnum GetBrawlerEnumBySkinEnum(BrawlersSkins BrawlerSkin) { return SkinEnumToBrawlerEnum[BrawlerSkin]; }
	BrawlersSkins GetDefaultSKinByBrawlerEnum(BrawlersEnum Brawler) { return BrawlerToDefaultSkin[Brawler]; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrawlersSkinsData")
		TMap<BrawlersSkins, FSkinPropereties> SkinEnumToSkin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrawlersSkinsData")
		TMap<BrawlersSkins, BrawlersEnum> SkinEnumToBrawlerEnum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrawlersSkinsData")
		TMap<BrawlersEnum, BrawlersSkins> BrawlerToDefaultSkin;
};
