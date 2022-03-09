// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AutoClickComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAutoclickAddSignature)

struct FMoneyStruct;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRAWLSTARSCLICKER_API UAutoClickComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	FOnAutoclickAddSignature OnAutoClickAdd;

	UAutoClickComponent();

	void SetMoneyToAdd(FMoneyStruct* MoneyToAdd) { Money = MoneyToAdd; }
	void SetSumToAdd(int32 NewSum) { SumToAdd = NewSum; }
	void SetAutoclickAvailable(bool Availablement) { IsAutoclickAvailable = Availablement; }
	void StartAutoClick();

private:
	FTimerHandle AutoclickTimer;

	bool IsAutoclickAvailable = false;
	int32 SumToAdd = 0;
	FMoneyStruct* Money = nullptr;

	void OnAutoclickTimer();
};
