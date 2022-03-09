// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuBrawler/MenuBrawler.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMenuBrawler::AMenuBrawler()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AMenuBrawler::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMenuBrawler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMenuBrawler::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

