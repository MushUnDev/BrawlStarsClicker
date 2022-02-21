// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DataWidget.h"
#include "Components/TextBlock.h"
#include "ClickerData/ClickerGameInstance.h"

void UDataWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UClickerGameInstance* GameInstance = Cast< UClickerGameInstance>(GetWorld()->GetGameInstance());
	GameInstance->OnCoinsCountChanged.AddUObject(this, &UDataWidget::OnCoinsDataTextUpdate);
}

void UDataWidget::OnCoinsDataTextUpdate(int32 ActuallyCoinsCount)
{
	CoinDataText->SetText(FText::FromString(FString("Coins: ") + FString::FromInt(ActuallyCoinsCount)));
}