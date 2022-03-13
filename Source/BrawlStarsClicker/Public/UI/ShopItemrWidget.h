// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClickerCoreData.h"
#include "ShopItemrWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnShopItemSignature, UShopItemrWidget*)

class UImage;
class UButton;
class UTextBlock;
class UTexture2D;

UCLASS()
class BRAWLSTARSCLICKER_API UShopItemrWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FOnShopItemSignature OnShopItem;

	void SetName(FText Name);
	void SetPrice(FText Price);
	void SetMoneyIcon(UTexture2D* Icon);
//	void SetPriceColor(FSlateColor Color);
	void SetItemIcon(UTexture2D* Icon);
	void SetBralwerEnum(BrawlersEnum BrawlerEn);
	void SetBoostEnum(BoostsEnum BoostEn);
	void SetSkinEnum(BrawlersSkins SkinEn);
	void SetCoinIconVisibility(ESlateVisibility Visivbility);

	BrawlersEnum GetCurrentBrawler() const { return CurrentBrawler; }
	BoostsEnum GetCurrentBoost() const { return CurrentBoost; }
	BrawlersSkins GetCurrentSkin() const { return CurrentSkin; }

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* BuyOrSelectButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* ItemNameText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* PriceText;

	UPROPERTY(meta = (BindWidget))
		UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
		UImage* CoinIcon;

	virtual void NativeOnInitialized() override;

private:
	BrawlersEnum CurrentBrawler = BrawlersEnum::Null;
	BoostsEnum CurrentBoost = BoostsEnum::Null;
	BrawlersSkins CurrentSkin = BrawlersSkins::Null;

	UFUNCTION()
	void ShopItem();
};
