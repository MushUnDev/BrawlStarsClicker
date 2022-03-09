// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ShopResourcesChapterWidget.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "UI/ShopItemrWidget.h"
#include "ClickerData/BoostsPrimaryDataAsset.h"
#include "ClickerData/ClickerGameInstance.h"
#include "ClickerData/ClickerSaveGame.h"

void UShopResourcesChapterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	/*auto GameInstance = Cast<UClickerGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;

	GameInstance->OnGameLoaded.AddUObject(this, &UShopResourcesChapterWidget::SetupAllShopItems);*/

	SetupAllShopItems();
}

void UShopResourcesChapterWidget::SetupAllShopItems()
{
	if (!GetWorld()) return;

	auto GameInstance = Cast<UClickerGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;

	auto BoostsInfoData = Cast<UBoostsPrimaryDataAsset>(GameInstance->GetBoostsInfoData());
	if (!BoostsInfoData) return;

	if (ShopChapter && BoostsInfoData)
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

				auto BoostInfo = BoostsInfoData->GetBoostInfoByEnum(BoostsList[ArrayCounter]);

				if (!BoostsInfoData) continue;

				ShopItem->SetName(BoostInfo->Name);
				ShopItem->SetItemIcon(BoostInfo->ShopIcon);
				ShopItem->SetBoostEnum(BoostsList[ArrayCounter]);
				
				if (BoostInfo->IsGemPrice) ShopItem->SetMoneyIcon(BoostInfo->GemIcon);

				if (GameInstance->IsBoostAvailable(BoostsList[ArrayCounter]))
				{
					ShopItem->SetCoinIconVisibility(ESlateVisibility::Hidden);

					ShopItem->SetPrice(FText::FromString(FString("Available")));
				}
				else
				{
					ShopItem->SetPrice(FMoneyStructUtils::GetTexted(&BoostInfo->Price));

					ShopItem->OnShopItem.AddUObject(this, &UShopResourcesChapterWidget::OnShopItem);
				}

				ArrayCounter++;
			}


		}
	}

}


void UShopResourcesChapterWidget::OnShopItem(UShopItemrWidget* BoostItem)
{
	auto GameInstance = Cast<UClickerGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;

	auto BoostsInfoData = Cast<UBoostsPrimaryDataAsset>(GameInstance->GetBoostsInfoData());
	if (!BoostsInfoData) return;

	auto BoostInfo = BoostsInfoData->GetBoostInfoByEnum(BoostItem->GetCurrentBoost());
	if (!BoostInfo) return;

	if (FMoneyStructUtils::TryToBuy(&BoostInfo->Price, BoostInfo->IsGemPrice ? GameInstance->GetCurrentGems() : GameInstance->GetCurrentMoney()))
	{
		FMoneyStructUtils::Buy(&BoostInfo->Price, BoostInfo->IsGemPrice ? GameInstance->GetCurrentGems() : GameInstance->GetCurrentMoney());

		BoostInfo->IsGemPrice ? GameInstance->OnGemsCountChanged.Broadcast(GameInstance->GetCurrentGems()) : GameInstance->OnCoinsCountChanged.Broadcast(GameInstance->GetCurrentMoney());
		GameInstance->AddAvailableBoost(BoostItem->GetCurrentBoost());

		BoostItem->SetCoinIconVisibility(ESlateVisibility::Hidden);
		BoostItem->SetPrice(FText::FromString(FString("Available")));

		BoostItem->OnShopItem.Clear();

		GameInstance->OnBuyingBoost.Broadcast(BoostItem->GetCurrentBoost());
	}
	else
	{
		//U CAN'T BUY
	}
}
