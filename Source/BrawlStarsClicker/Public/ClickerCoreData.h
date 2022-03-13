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
	Null,
	Colt UMETA(DisplayName = "Colt"),
	Shelly UMETA(DisplayName = "Shelly"),
	Barley UMETA(DisplayName = "Barley"),
	El_Primo UMETA(DisplayName = "El Primo"),
	Leon UMETA(DisplayName = "Leon"),
	EightBit UMETA(DisplayName = "8-bit"),
	Crow UMETA(DisplayName = "Crow")
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
	Null,
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

UENUM(BlueprintType)
enum class BrawlersSkins : uint8
{
	Null UMETA(DisplayName = "NULL"),
	//Shelly
	Shelly_Default UMETA(DisplayName = "Shelly Default"),
	Shelly_Bandit UMETA(DisplayName = "Shelly Bandit"),
	Shelly_Witch UMETA(DisplayName = "Shelly Witch"),

	//Crown
	Crow_Default UMETA(DisplayName = "Crow Default"),
	Crow_White UMETA(DisplayName = "Crow White"),
	Crow_Phenix UMETA(DisplayName = "Crow Phenix"),

	//Colt
	Colt_Default UMETA(DisplayName = "Colt Default"),
	Colt_Royal_Agent UMETA(DisplayName = "Colt Royal Agent"),
	Colt_Rockstar UMETA(DisplayName = "Colt Rockstar"),

	//Barley
	Barley_Default UMETA(DisplayName = "Barley Default"),
	Barley_Banker UMETA(DisplayName = "Barley Banker"),
	Barley_Lamberjack UMETA(DisplayName = "Barley Lamberjack"),

	//El Primo
	El_Pirmo_Default UMETA(DisplayName = "El Primo Default"),
	El_Pirmo_Rudo UMETA(DisplayName = "El Primo Rudo"),
	El_Pirmo_Ray UMETA(DisplayName = "El Primo Ray"),

	//Leon
	Leon_Default UMETA(DisplayName = "Leon Default"),
	Leon_Shark UMETA(DisplayName = "Leon Shark"),
	Leon_Gold UMETA(DisplayName = "Leon Gold"),
};

USTRUCT(BlueprintType)
struct FSkinPropereties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkinsProperties")
		FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkinsProperties")
		bool IsDefaultSkin = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkinsProperties", meta = (EditCondition = "!IsDefaultSkin"))
		FMoneyStruct Price;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkinsProperties")
		USkeletalMesh* Skin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkinsProperties", meta = (EditCondition = "!IsDefaultSkin"))
		UTexture2D* ShopIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkinsProperties", meta = (EditCondition = "!IsDefaultSkin"))
		bool IsGemPrice = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkinsProperties", meta = (EditCondition = "IsGemPrice && !IsDefaultSkin"))
		UTexture2D* GemIcon;
};