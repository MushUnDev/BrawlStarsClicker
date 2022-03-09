// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterChapterWidget.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "UI/ShopItemrWidget.h"
#include "ClickerData/BrawlersPrimaryDataAsset.h"
#include "ClickerData/ClickerGameInstance.h"
#include "ClickerData/ClickerSaveGame.h"

void UCharacterChapterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	/*auto GameInstance = Cast<UClickerGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;

	GameInstance->OnGameLoaded.AddUObject(this, &UCharacterChapterWidget::SetupAllShopItems);*/

	SetupAllShopItems();
}

void UCharacterChapterWidget::SetupAllShopItems()
{
	if (!GetWorld()) return;

	auto GameInstance = Cast<UClickerGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;

	auto BrawlersInfoData = Cast<UBrawlersPrimaryDataAsset>(GameInstance->GetBrawlersInfoData());

	if (ShopChapter && BrawlersInfoData)
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
				
				auto BrawlerInfo = BrawlersInfoData->GetBrawlerInfoByEnum(BrawlersList[ArrayCounter]);

				if (!BrawlerInfo) continue;

				ShopItem->SetName(BrawlerInfo->Name);
				ShopItem->SetItemIcon(BrawlerInfo->ShopIcon);
				ShopItem->SetBralwerEnum(BrawlersList[ArrayCounter]);

				if (GameInstance->IsBrawlerAvailable(BrawlersList[ArrayCounter]))
				{
					ShopItem->SetCoinIconVisibility(ESlateVisibility::Hidden);
					ShopItem->OnShopItem.AddUObject(this, &UCharacterChapterWidget::OnAvailableItem);

					if (GameInstance->IsBrawlerCurrent(BrawlersList[ArrayCounter]))
					{
						ShopItem->SetPrice(FText::FromString(FString("Selected")));
						CurrentBrawlerShopItemWidget = ShopItem;
					}
					else
					{
						ShopItem->SetPrice(FText::FromString(FString("Select")));
					}
				}
				else
				{
					ShopItem->SetPrice(FMoneyStructUtils::GetTexted(&BrawlerInfo->Price));

					ShopItem->OnShopItem.AddUObject(this, &UCharacterChapterWidget::OnShopItem);
				}

				ArrayCounter++;
			}
			

		}
	}

}


void UCharacterChapterWidget::OnShopItem(UShopItemrWidget* BrawlerItem)
{
	auto GameInstance = Cast<UClickerGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;

	auto BrawlersInfoData = Cast<UBrawlersPrimaryDataAsset>(GameInstance->GetBrawlersInfoData());
	if (!BrawlersInfoData) return;

	auto BrawlerInfo = BrawlersInfoData->GetBrawlerInfoByEnum(BrawlerItem->GetCurrentBrawler());
	if (!BrawlerInfo) return;

	if (FMoneyStructUtils::TryToBuy(&BrawlerInfo->Price, GameInstance->GetCurrentMoney()))
	{
		FMoneyStructUtils::Buy(&BrawlerInfo->Price, GameInstance->GetCurrentMoney());

		GameInstance->OnCoinsCountChanged.Broadcast(GameInstance->GetCurrentMoney());
		GameInstance->AddAvailableBrawler(BrawlerItem->GetCurrentBrawler());
		GameInstance->SetClickerCoefficient(BrawlerInfo->ClickCoefficient);

		BrawlerItem->SetCoinIconVisibility(ESlateVisibility::Hidden);
		BrawlerItem->SetPrice(FText::FromString(FString("Select")));

		BrawlerItem->OnShopItem.Clear();
		BrawlerItem->OnShopItem.AddUObject(this, &UCharacterChapterWidget::OnAvailableItem);
	}
	else
	{
		//U CAN'T BUY
	}
}

void UCharacterChapterWidget::OnAvailableItem(UShopItemrWidget* BrawlerItem)
{
	if (!GetWorld() || !BrawlerItem) return;

	CurrentBrawlerShopItemWidget->SetPrice(FText::FromString("Select"));
	//CurrentBrawlerShopItemWidget->SetPriceColor(FLinearColor(1.f, 1.f, 1.f));

	BrawlerItem->SetPrice(FText::FromString("Selected"));
	//BrawlerItem->SetPriceColor(FLinearColor(0.2f, 0.8f, 0.2f));


	auto GameInstance = Cast<UClickerGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance) return;

	auto BrawlersInfoData = Cast<UBrawlersPrimaryDataAsset>(GameInstance->GetBrawlersInfoData());
	if (!BrawlersInfoData) return;

	auto BrawlerInfo = BrawlersInfoData->GetBrawlerInfoByEnum(BrawlerItem->GetCurrentBrawler());
	if (!BrawlerInfo) return;

	if (*GameInstance->GetCurrentBrawler() == BrawlerItem->GetCurrentBrawler()) return;

	auto CurrentBrawlerClassCopy = GameInstance->GetCurrentBrawlerClass();

	GameInstance->SetCurrentBrawlerClass(GetWorld()->SpawnActorAbsolute(BrawlerInfo->BrawlerClass, BrawlersInfoData->GetBrawlerTransform()));

	CurrentBrawlerClassCopy->Destroy();

	*GameInstance->GetCurrentBrawler() = BrawlerItem->GetCurrentBrawler();

	CurrentBrawlerShopItemWidget = BrawlerItem;

	GameInstance->SetClickerCoefficient(BrawlerInfo->ClickCoefficient);

	GameInstance->OnBrawlerChanged.Broadcast(BrawlerItem->GetCurrentBrawler());
}