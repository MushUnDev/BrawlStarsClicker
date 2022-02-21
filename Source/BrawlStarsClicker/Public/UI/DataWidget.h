// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataWidget.generated.h"

class UTextBlock;

UCLASS()
class BRAWLSTARSCLICKER_API UDataWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CoinDataText;

	virtual void NativeOnInitialized() override;

private:
	void OnCoinsDataTextUpdate(int32 ActuallyCoinsCount);
};
