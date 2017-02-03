// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "AITankController.h"

#include "Tank.h"


void AAITankController::BeginPlay()
{
	Super::BeginPlay();

	// check my own tank
	ATank* myTank = GetControlledTank();

	if (myTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI %s has controlled tank %s"), *GetName(), *myTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AI %s does not have controlled tank!"), *GetName());
	}

	// check the player's tank
	ATank* playerTank = GetPlayerTank();

	if (playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI %s found player tank %s"), *GetName(), *playerTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AI %s couldn't find the player's tank!"), *GetName());
	}
}

void AAITankController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// TODO move towards the player
	
	AimTowardsPlayer();

	// TODO fire the gun if ready
}

ATank* AAITankController::GetControlledTank() const
{
	auto tank = GetPawn();
	return (tank)? Cast<ATank>(tank) : nullptr;
}

ATank* AAITankController::GetPlayerTank() const
{
	auto tank = GetWorld()->GetFirstPlayerController()->GetPawn();
	return (tank)? Cast<ATank>(tank) : nullptr;
}

void AAITankController::AimTowardsPlayer()
{
	if (!GetControlledTank()) return;

	ATank* target = GetPlayerTank();

	if (target) {
		GetControlledTank()->AimAt(target->GetActorLocation());
	}
}
