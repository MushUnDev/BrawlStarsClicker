// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataWidget.generated.h"

class UTextBlock;
struct FMoneyStruct;

UCLASS()
class BRAWLSTARSCLICKER_API UDataWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CoinsDataText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* GemsDataText;

	virtual void NativeOnInitialized() override;

private:
	void OnCoinsDataTextUpdate(FMoneyStruct* ActuallyCoinsCount);
	void OnGemsDataTextUpdate(FMoneyStruct* ActuallyCoinsCount);
};
