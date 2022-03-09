#pragma once

#include "CoreMinimal.h"
#include "ClickerCoreData.generated.h"

USTRUCT(BlueprintType)
struct FMoneyStruct
{
	GENERATED_USTRUCT_BODY()

	FMoneyStruct() {}

	FMoneyStruct(int32 Th, int32 Mil, int32 Bil, int32 Tr)
	{
		Thousands = Th;
		Millions = Mil;
		Billions = Bil;
		Trillions = Tr;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Price", meta = (ClampMin = 0, ClampMax = 999))
		int32 Thousands;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Price", meta = (ClampMin = 0, ClampMax = 999))
		int32 Millions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Price", meta = (ClampMin = 0, ClampMax = 999))
		int32 Billions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Price", meta = (ClampMin = 0, ClampMax = 999))
		int32 Trillions;

};

class FMoneyStructUtils
{

public:
	static void Add(FMoneyStruct* MoneyStruct, int32 ToAdd)
	{
		MoneyStruct->Thousands += GetLastThree(ToAdd);
		MoneyStruct->Millions += GetLastThree(ToAdd);
		MoneyStruct->Billions += GetLastThree(ToAdd);
		MoneyStruct->Trillions += GetLastThree(ToAdd);

		Normilize(MoneyStruct);
	}

	static int32 GetLastThree(int32& ToGet)
	{
		if (ToGet == 0) return 0;

		int32 LastTree = ToGet % 1000;

		ToGet /= 1000;

		return LastTree;
	}

	static void Normilize(FMoneyStruct* MoneyStruct)
	{
		MoneyStruct->Millions += GetNormilized(MoneyStruct->Thousands);
		MoneyStruct->Billions += GetNormilized(MoneyStruct->Millions);
		MoneyStruct->Trillions += GetNormilized(MoneyStruct->Billions);

	}

	static int32 GetNormilized(int32& ToNormilize)
	{
		if (ToNormilize > 999)
		{
			int32 Normilized = ToNormilize / 1000;
			ToNormilize %= 1000;
			return Normilized;
		}
		else
		{
			return 0;
		}
	}

	static FText GetTexted(FMoneyStruct* MoneyStruct)
	{
		if (MoneyStruct->Trillions > 0)
		{
			if(MoneyStruct->Billions < 10) return FText::FromString(FString::FromInt(MoneyStruct->Trillions) + ".00" + FString::FromInt(MoneyStruct->Billions) + "B");
			if(MoneyStruct->Billions < 100) return FText::FromString(FString::FromInt(MoneyStruct->Trillions) + ".0" + FString::FromInt(MoneyStruct->Billions) + "B");
			return FText::FromString(FString::FromInt(MoneyStruct->Trillions) + "." + FString::FromInt(MoneyStruct->Billions) + "B");
		}

		if (MoneyStruct->Billions > 0)
		{
			if(MoneyStruct->Millions < 10) return FText::FromString(FString::FromInt(MoneyStruct->Billions) + ".00" + FString::FromInt(MoneyStruct->Millions) + "M");
			if(MoneyStruct->Millions < 100) return FText::FromString(FString::FromInt(MoneyStruct->Billions) + ".0" + FString::FromInt(MoneyStruct->Millions) + "M");
			return FText::FromString(FString::FromInt(MoneyStruct->Billions) + "." + FString::FromInt(MoneyStruct->Millions) + "M");
		}

		if (MoneyStruct->Millions > 0)
		{
			if (MoneyStruct->Thousands < 10) return FText::FromString(FString::FromInt(MoneyStruct->Millions) + ".00" + FString::FromInt(MoneyStruct->Thousands) + "K");
			if (MoneyStruct->Thousands < 100) return FText::FromString(FString::FromInt(MoneyStruct->Millions) + ".0" + FString::FromInt(MoneyStruct->Thousands) + "K");
			return FText::FromString(FString::FromInt(MoneyStruct->Millions) + "." + FString::FromInt(MoneyStruct->Thousands) + "K");
		}

		return FText::FromString(FString::FromInt(MoneyStruct->Thousands));
	}

	static bool TryToBuy(FMoneyStruct* Price, FMoneyStruct* CurrentMoney)
	{
		if (CurrentMoney->Trillions > Price->Trillions) return true;
		else if (CurrentMoney->Billions > Price->Billions && CurrentMoney->Trillions == Price->Trillions) return true;
		else if (CurrentMoney->Millions > Price->Millions && CurrentMoney->Billions == Price->Billions && CurrentMoney->Trillions == Price->Trillions) return true;
		else if (CurrentMoney->Thousands >= Price->Thousands && CurrentMoney->Millions == Price->Millions && CurrentMoney->Billions == Price->Billions && CurrentMoney->Trillions == Price->Trillions) return true;
		else return false;
	}

	static void Buy(FMoneyStruct* Price, FMoneyStruct* CurrentMoney)
	{
		CurrentMoney->Thousands = CurrentMoney->Thousands - Price->Thousands;
		CurrentMoney->Millions = CurrentMoney->Millions - Price->Millions;
		CurrentMoney->Billions = CurrentMoney->Billions - Price->Billions;
		CurrentMoney->Trillions = CurrentMoney->Trillions - Price->Trillions;

		if (CurrentMoney->Thousands < 0)
		{
			CurrentMoney->Thousands += 1000;
			CurrentMoney->Millions--;
		}

		if (CurrentMoney->Millions < 0)
		{
			CurrentMoney->Millions += 1000;
			CurrentMoney->Billions--;
		}

		if (CurrentMoney->Billions < 0)
		{
			CurrentMoney->Billions += 1000;
			CurrentMoney->Trillions--;
		}

	}

};

UENUM(BlueprintType)
enum class BrawlersEnum : uint8
{
	Colt UMETA(DisplayName = "Colt"),
	Shelly UMETA(DisplayName = "Shelly"),
	Barley UMETA(DisplayName = "Barley"),
	El_Primo UMETA(DisplayName = "El Primo"),
	Leon UMETA(DisplayName = "Leon"),
	EightBit UMETA(DisplayName = "8-bit")
};

USTRUCT(BlueprintType)
struct FBrawlerPropereties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrawlerProperties")
		FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrawlerProperties")
		FMoneyStruct Price;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrawlerProperties")
		int32 ClickCoefficient;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrawlerProperties")
		TSubclassOf<AActor> BrawlerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrawlerProperties")
		UTexture2D* ShopIcon;
};

UENUM(BlueprintType)
enum class BoostsEnum : uint8
{
	ClickRash,
	AutoClick,
	BigRandomClick,
	RandomGemClick
};

USTRUCT(BlueprintType)
struct FBoostsPropereties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BoostsProperties")
		FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BoostsProperties")
		FMoneyStruct Price;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BoostsProperties")
		UTexture2D* ShopIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BoostsProperties")
		bool IsGemPrice = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BoostsProperties", meta = (EditCondition = "IsGemPrice"))
		UTexture2D* GemIcon;
};