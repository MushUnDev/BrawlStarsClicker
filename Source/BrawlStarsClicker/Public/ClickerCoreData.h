#pragma once

#include "CoreMinimal.h"
#include "ClickerCoreData.generated.h"

USTRUCT(BlueprintType)
struct FClickerData
{
	GENERATED_USTRUCT_BODY();

	// Realize struct for very big date (k, kk and exc)
	int32 Coins = 0;

	int32 Gems = 0;

};
