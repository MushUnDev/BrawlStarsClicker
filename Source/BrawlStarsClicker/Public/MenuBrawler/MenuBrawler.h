// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MenuBrawler.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class BRAWLSTARSCLICKER_API AMenuBrawler : public ACharacter
{
	GENERATED_BODY()

public:
	AMenuBrawler();

protected:
	//Properties
	UPROPERTY(Visibleanywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* CameraComponent;

	UPROPERTY(Visibleanywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArmComponent;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
