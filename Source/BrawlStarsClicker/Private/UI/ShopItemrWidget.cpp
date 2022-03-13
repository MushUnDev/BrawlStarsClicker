// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ShopItemrWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "ClickerCoreData.h"

void UShopItemrWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (BuyOrSelectButton)
	{
		BuyOrSelectButton->OnClicked.AddDynamic(this, &UShopItemrWidget::ShopItem);
	}
}

void UShopItemrWidget::ShopItem()
{
	OnShopItem.Broadcast(this);
}

void UShopItemrWidget::SetName(FText Name)
{
	if (!ItemNameText) return;

	ItemNameText->SetText(Name);
}

void UShopItemrWidget::SetPrice(FText Price)
{
	if (!PriceText) return;

	PriceText->SetText(Price);
}

void UShopItemrWidget::SetItemIcon(UTexture2D* Icon)
{
	if (!ItemIcon) return;

	ItemIcon->SetBrushFromTexture(Icon);
}

void UShopItemrWidget::SetMoneyIcon(UTexture2D* Icon)
{
	if (!ItemIcon) return;

	CoinIcon->SetBrushFromTexture(Icon);
}

void UShopItemrWidget::SetBralwerEnum(BrawlersEnum BrawlerEn)
{
	CurrentBrawler = BrawlerEn;
}

void UShopItemrWidget::SetBoostEnum(BoostsEnum BoostEn)
{
	CurrentBoost = BoostEn;
}

void UShopItemrWidget::SetSkinEnum(BrawlersSkins SkinEn)
{
	CurrentSkin = SkinEn;
}

void UShopItemrWidget::SetCoinIconVisibility(ESlateVisibility Visivbility)
{
	CoinIcon->SetVisibility(Visivbility); 
}

//void UShopItemrWidget::SetPriceColor(FSlateColor Color)
//{
//	if (!PriceText) return;
//
//	PriceText->SetColorAndOpacity(Color);
//}