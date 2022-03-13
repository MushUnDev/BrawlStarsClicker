// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BralwersSkinsChapterWidget.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "UI/ShopItemrWidget.h"
#include "ClickerData/BrawlersSkinsPrimaryDataAsset.h"
#include "ClickerData/ClickerGameInstance.h"
#include "ClickerData/ClickerSaveGame.h"
#include "GameFramework/Character.h"
#include "ClickerCoreData.h"

void UBralwersSkinsChapterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	/*auto GameInstance = Cast<UClickerGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;

	GameInstance->OnGameLoaded.AddUObject(this, &UBralwersSkinsChapterWidget::SetupAllShopItems);*/

	SetupAllShopItems();
}

void UBralwersSkinsChapterWidget::SetupAllShopItems()
{
	if (!GetWorld()) return;

	auto GameInstance = Cast<UClickerGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;

	GameInstance->OnBrawlerChanged.AddUObject(this, &UBralwersSkinsChapterWidget::OnBrawlerChanged);

	auto SkinsInfoData = Cast<UBrawlersSkinsPrimaryDataAsset>(GameInstance->GetSkinsInfoData());

	if (ShopChapter && SkinsInfoData)
	{
		auto AllChildren = ShopChapter->GetAllChildren();
		int8 ArrayCounter = 0;

		for (auto Child : AllChildren)
		{
			auto ShopItemRow = Cast<UHorizontalBox>(Child);

			if (!ShopItemRow) continue;

			auto AllRowChildren = ShopItemRow->GetAllChildren();

			for (auto RowChildren : AllRowChildren)
			{
				auto ShopItem = Cast<UShopItemrWidget>(RowChildren);

				if (!ShopItem) continue;

				auto SkinInfo = SkinsInfoData->GetSkinProperitiesByEnum(BrawlersList[ArrayCounter]);

				if (!SkinInfo) continue;

				ShopItem->SetName(SkinInfo->Name);
				ShopItem->SetItemIcon(SkinInfo->ShopIcon);
				ShopItem->SetSkinEnum(BrawlersList[ArrayCounter]);

				if (SkinInfo->IsGemPrice) ShopItem->SetMoneyIcon(SkinInfo->GemIcon);

				if (GameInstance->IsSkinAvailable(BrawlersList[ArrayCounter]))
				{
					ShopItem->SetCoinIconVisibility(ESlateVisibility::Hidden);
					ShopItem->OnShopItem.AddUObject(this, &UBralwersSkinsChapterWidget::OnAvailableItem);

					if (GameInstance->IsSkinCurrent(BrawlersList[ArrayCounter]))
					{
						ShopItem->SetPrice(FText::FromString(FString("Selected")));
						CurrentSkinShopItemWidget = ShopItem;
					}
					else
					{
						ShopItem->SetPrice(FText::FromString(FString("Select")));
					}
				}
				else
				{
					ShopItem->SetPrice(FMoneyStructUtils::GetTexted(&SkinInfo->Price));

					ShopItem->OnShopItem.AddUObject(this, &UBralwersSkinsChapterWidget::OnShopItem);
				}

				ArrayCounter++;
			}


		}
	}

}


void UBralwersSkinsChapterWidget::OnShopItem(UShopItemrWidget* SkinItem)
{
	auto GameInstance = Cast<UClickerGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;

	auto SkinsInfoData = Cast<UBrawlersSkinsPrimaryDataAsset>(GameInstance->GetSkinsInfoData());
	if (!SkinsInfoData) return;

	auto SkinInfo = SkinsInfoData->GetSkinProperitiesByEnum(SkinItem->GetCurrentSkin());
	if (!SkinInfo) return;

	if (FMoneyStructUtils::TryToBuy(&SkinInfo->Price, SkinInfo->IsGemPrice ? GameInstance->GetCurrentGems() : GameInstance->GetCurrentMoney()))
	{
		FMoneyStructUtils::Buy(&SkinInfo->Price, SkinInfo->IsGemPrice ? GameInstance->GetCurrentGems() : GameInstance->GetCurrentMoney());

		SkinInfo->IsGemPrice ? GameInstance->OnGemsCountChanged.Broadcast(GameInstance->GetCurrentGems()) : GameInstance->OnCoinsCountChanged.Broadcast(GameInstance->GetCurrentMoney());
		GameInstance->AddAvailableBoost(SkinItem->GetCurrentBoost());

		SkinItem->SetCoinIconVisibility(ESlateVisibility::Hidden);
		SkinItem->SetPrice(FText::FromString(FString("Available")));

		SkinItem->OnShopItem.Clear();
		SkinItem->OnShopItem.AddUObject(this, &UBralwersSkinsChapterWidget::OnAvailableItem);

		GameInstance->OnBuyingBoost.Broadcast(SkinItem->GetCurrentBoost());
	}
	else
	{
		//U CAN'T BUY
	}
}

void UBralwersSkinsChapterWidget::OnAvailableItem(UShopItemrWidget* SkinItem)
{
	if (!GetWorld() || !SkinItem) return;

	auto GameInstance = Cast<UClickerGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;

	auto SkinsInfoData = Cast<UBrawlersSkinsPrimaryDataAsset>(GameInstance->GetSkinsInfoData());
	if (!SkinsInfoData) return;

	auto SkinInfo = SkinsInfoData->GetSkinProperitiesByEnum(SkinItem->GetCurrentSkin());
	if (!SkinInfo) return;

	if (*GameInstance->GetCurrentSkin() == SkinItem->GetCurrentSkin() || *GameInstance->GetCurrentBrawler() != SkinsInfoData->GetBrawlerEnumBySkinEnum(SkinItem->GetCurrentSkin())) return;

	if (CurrentSkinShopItemWidget)
	{
		CurrentSkinShopItemWidget->SetPrice(FText::FromString("Select"));
		//CurrentBrawlerShopItemWidget->SetPriceColor(FLinearColor(1.f, 1.f, 1.f));
	}

	SkinItem->SetPrice(FText::FromString("Selected"));
	//BrawlerItem->SetPriceColor(FLinearColor(0.2f, 0.8f, 0.2f));


	Cast<ACharacter>(GameInstance->GetCurrentBrawlerClass())->GetMesh()->SetSkeletalMesh(SkinInfo->Skin);

	*GameInstance->GetCurrentSkin() = SkinItem->GetCurrentSkin();

	CurrentSkinShopItemWidget = SkinItem;

}

void UBralwersSkinsChapterWidget::OnBrawlerChanged(BrawlersEnum NewBrawler)
{
	auto GameInstance = Cast<UClickerGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;

	auto SkinsInfoData = Cast<UBrawlersSkinsPrimaryDataAsset>(GameInstance->GetSkinsInfoData());
	if (!SkinsInfoData) return;

	if (*GameInstance->GetCurrentBrawler() == NewBrawler)
	{
		auto SkinInfoDefault = SkinsInfoData->GetSkinProperitiesByEnum(SkinsInfoData->GetDefaultSKinByBrawlerEnum(NewBrawler));
		if (!SkinInfoDefault) return;

		*GameInstance->GetCurrentSkin() = SkinsInfoData->GetDefaultSKinByBrawlerEnum(NewBrawler);

		Cast<ACharacter>(GameInstance->GetCurrentBrawlerClass())->GetMesh()->SetSkeletalMesh(SkinInfoDefault->Skin);
	}

	if (!CurrentSkinShopItemWidget) return;

	CurrentSkinShopItemWidget->SetPrice(FText::FromString("Select"));

	CurrentSkinShopItemWidget = nullptr;
}