// Fill out your copyright notice in the Description page of Project Settings.


#include "Boosts/AutoClickComponent.h"
#include "ClickerCoreData.h"

DEFINE_LOG_CATEGORY_STATIC(LogAutoclickComponent, All, All)

UAutoClickComponent::UAutoClickComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAutoClickComponent::StartAutoClick()
{
	if (!IsAutoclickAvailable || !GetWorld()) return;

	if (GetWorld()->GetTimerManager().IsTimerActive(AutoclickTimer)) return;

	GetWorld()->GetTimerManager().SetTimer(AutoclickTimer, this, &UAutoClickComponent::OnAutoclickTimer, 1.f, true);
}

void UAutoClickComponent::OnAutoclickTimer()
{
	FMoneyStructUtils::Add(Money, SumToAdd);
	
	OnAutoClickAdd.Broadcast();
}