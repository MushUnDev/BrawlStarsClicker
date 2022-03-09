// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DataWidget.h"
#include "Components/TextBlock.h"
#include "ClickerData/ClickerGameInstance.h"
#include "ClickerCoreData.h"

void UDataWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UClickerGameInstance* GameInstance = Cast< UClickerGameInstance>(GetWorld()->GetGameInstance());
	GameInstance->OnCoinsCountChanged.AddUObject(this, &UDataWidget::OnCoinsDataTextUpdate);
	GameInstance->OnGemsCountChanged.AddUObject(this, &UDataWidget::OnGemsDataTextUpdate);
}

void UDataWidget::OnCoinsDataTextUpdate(FMoneyStruct* ActuallyCoinsCount)
{
	CoinsDataText->SetText(FMoneyStructUtils::GetTexted(ActuallyCoinsCount));
}

void UDataWidget::OnGemsDataTextUpdate(FMoneyStruct* ActuallyGemsCount)
{
	GemsDataText->SetText(FMoneyStructUtils::GetTexted(ActuallyGemsCount));
}