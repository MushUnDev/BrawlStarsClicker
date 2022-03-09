// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RandomBigClickComponent.generated.h"

struct FMoneyStruct;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRAWLSTARSCLICKER_API URandomBigClickComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URandomBigClickComponent();

	void SetRandomBigClickAvailable(bool Availablement) { IsRandomBigClickAvailable = Availablement; }
	void SetRandomBigClickCoefficient(int32 CurrentClickCoefficient) { ClickCoefficient = CurrentClickCoefficient; }
	void SetMoneyToAdd(FMoneyStruct* MoneyToAdd) { Coins = MoneyToAdd; }

	bool RandomAddCoins();

private:
	bool IsRandomBigClickAvailable = false;
	int32 ClickCoefficient = 0.f;
	FMoneyStruct* Coins;

	bool GemClickOrNot() const;
};
