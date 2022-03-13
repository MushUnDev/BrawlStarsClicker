// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnShopSignature, bool);

class UButton;
class UOverlay;

UCLASS()
class BRAWLSTARSCLICKER_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnShopSignature OnShop;
	
protected:
	UPROPERTY(meta = (BindWidget))
		UButton* ShopButton;

	UPROPERTY(meta = (BindWidget))
		UOverlay* ShopOverlay;

	virtual void NativeOnInitialized() override;

private:
	bool ShopVisibility = false;

	UFUNCTION()
		void Shop();
};
