// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BralwersSkinsChapterWidget.generated.h"

class UVerticalBox;
class UShopItemrWidget;
enum class BrawlersSkins : uint8;
enum class BrawlersEnum : uint8;

UCLASS()
class BRAWLSTARSCLICKER_API UBralwersSkinsChapterWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
		UVerticalBox* ShopChapter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ShopList")
		TArray<BrawlersSkins> BrawlersList;

	virtual void NativeOnInitialized() override;

private:
	UShopItemrWidget* CurrentSkinShopItemWidget = nullptr;

	void SetupAllShopItems();

	void OnShopItem(UShopItemrWidget* SkinItem);

	void OnAvailableItem(UShopItemrWidget* SkinItem);

	void OnBrawlerChanged(BrawlersEnum NewBrawler);
};
