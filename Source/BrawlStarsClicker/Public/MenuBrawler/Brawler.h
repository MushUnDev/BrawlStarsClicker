// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Brawler.generated.h"

UCLASS()
class BRAWLSTARSCLICKER_API ABrawler : public ACharacter
{
	GENERATED_BODY()

public:
	ABrawler();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
