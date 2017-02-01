// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "PlayerTankController.h"


void APlayerTankController::BeginPlay()
{
	Super::BeginPlay();

	ATank* myTank = GetControlledTank();

	if (myTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player has controlled tank %s"), *myTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Player does not have controlled tank!"));
	}
}

void APlayerTankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ATank* APlayerTankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void APlayerTankController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;

	// get the world location of a linetrace through the crosshair
	// start moving the turret and barrel to point at that world location
}
