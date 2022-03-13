// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClickerCoreData.h"
#include "CharacterChapterWidget.generated.h"

class UVerticalBox;
class UShopItemrWidget;


UCLASS()
class BRAWLSTARSCLICKER_API UCharacterChapterWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* ShopChapter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ShopList")
		TArray<BrawlersEnum> BrawlersList;

	virtual void NativeOnInitialized() override;

private:
	UShopItemrWidget* CurrentBrawlerShopItemWidget;

	void SetupAllShopItems();

	void OnShopItem(UShopItemrWidget* BrawlerItem);

	void OnAvailableItem(UShopItemrWidget* BrawlerItem);
};
