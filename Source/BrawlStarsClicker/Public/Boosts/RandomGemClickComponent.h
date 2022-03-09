// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RandomGemClickComponent.generated.h"

struct FMoneyStruct;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRAWLSTARSCLICKER_API URandomGemClickComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URandomGemClickComponent();

	void SetRandomGemClickAvailable(bool Availablement) { IsRandomGemClickAvailable = Availablement; }
	void SetMoneyToAdd(FMoneyStruct* MoneyToAdd) { Gems = MoneyToAdd; }

	bool RandomAddGem();

private:
	bool IsRandomGemClickAvailable = false;
	FMoneyStruct* Gems;

	bool GemClickOrNot() const;
};
