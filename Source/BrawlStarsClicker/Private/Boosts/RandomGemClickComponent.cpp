// Fill out your copyright notice in the Description page of Project Settings.


#include "Boosts/RandomGemClickComponent.h"
#include "Math/UnrealMathUtility.h"
#include "ClickerCoreData.h"

URandomGemClickComponent::URandomGemClickComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

bool URandomGemClickComponent::GemClickOrNot() const
{
	return FMath::RandRange(0, 100) * FMath::RandRange(0, 100) == FMath::RandRange(0, 100);
}

bool URandomGemClickComponent::RandomAddGem()
{
	if (!IsRandomGemClickAvailable || !GemClickOrNot()) return false;

	FMoneyStructUtils::Add(Gems, 1);

	return true;
}