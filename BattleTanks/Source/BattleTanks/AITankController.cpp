// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "AITankController.h"

#include "TankAimingComponent.h"
#include "Tank.h"


void AAITankController::BeginPlay()
{
	Super::BeginPlay();
}

void AAITankController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// get references 
	auto targetTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(targetTank)) return;

	auto myTank = GetPawn();
	if (!ensure(myTank)) return;

	// move towards the target
	MoveToActor(targetTank, ApproachDistance);

	// aim towards the target and fire
	auto fireControl = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(fireControl)) return;
	fireControl->AimAt(targetTank->GetActorLocation());

	// only fire when our aim is locked?
	if (fireControl->GetFiringState() == EFiringState::Locked) {
		//fireControl->Fire();
	}
}

void AAITankController::SetPawn(APawn * Pawn)
{
	Super::SetPawn(Pawn);

	if (Pawn) {
		ATank* possessedTank = Cast<ATank>(Pawn);

		if (!ensure(possessedTank)) return;

		possessedTank->OnTankDeath.AddUniqueDynamic(this, &AAITankController::OnPossessedTankDeath);
	}
}

void AAITankController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s possessed tank death!"), *GetName());
}
