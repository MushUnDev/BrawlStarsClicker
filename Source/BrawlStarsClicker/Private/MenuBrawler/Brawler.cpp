// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuBrawler/Brawler.h"

ABrawler::ABrawler()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABrawler::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABrawler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrawler::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

