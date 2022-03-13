// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClickerCoreData.h"
#include "ShopResourcesChapterWidget.generated.h"

class UVerticalBox;
class UShopItemrWidget;

UCLASS()
class BRAWLSTARSCLICKER_API UShopResourcesChapterWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* ShopChapter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ShopList")
		TArray<BoostsEnum> BoostsList;

	virtual void NativeOnInitialized() override;

private:
	void SetupAllShopItems();

	void OnShopItem(UShopItemrWidget* BoostItem);
};
