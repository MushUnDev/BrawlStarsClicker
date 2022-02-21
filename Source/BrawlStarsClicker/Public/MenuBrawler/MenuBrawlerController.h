// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuBrawlerController.generated.h"

class UClickerGameInstance;

UCLASS()
class BRAWLSTARSCLICKER_API AMenuBrawlerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMenuBrawlerController();

protected:
	virtual bool InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex) override;
	//void GetInputTouchState(ETouchIndex::Type FingerIndex, float& LocationX, float& LocationY, bool& bIsCurrentlyPressed) const override;

private:
	bool IsPressed = false;
	UClickerGameInstance* GameInstance;

	bool TouchBegan();
	bool TouchEnded();
};
