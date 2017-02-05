// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "AITankController.h"

#include "Tank.h"


void AAITankController::BeginPlay()
{
	Super::BeginPlay();
}

void AAITankController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// get references
	auto myTank = Cast<ATank>(GetPawn());
	auto targetTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (ensure(myTank && targetTank)) {
		// move towards the player
		MoveToActor(targetTank, ApproachDistance);

		// aim towards the target
		myTank->AimAt(targetTank->GetActorLocation());

		// TODO fire the gun if ready
		myTank->Fire();
	}
}
