// Fill out your copyright notice in the Description page of Project Settings.


#include "Boosts/RandomBigClickComponent.h"
#include "Math/UnrealMathUtility.h"
#include "ClickerCoreData.h"

URandomBigClickComponent::URandomBigClickComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

bool URandomBigClickComponent::GemClickOrNot() const
{
	return FMath::RandRange(0, 100) == FMath::RandRange(0, 100);
}

bool URandomBigClickComponent::RandomAddCoins()
{
	if (!IsRandomBigClickAvailable || !GemClickOrNot()) return false;

	FMoneyStructUtils::Add(Coins, ClickCoefficient * 100);

	return true;
}