// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "PlayerTankController.h"

#include "TankAimingComponent.h"
#include "Tank.h"


void APlayerTankController::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerTankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void APlayerTankController::SetPawn(APawn * Pawn)
{
	Super::SetPawn(Pawn);

	if (Pawn) {
		ATank* possessedTank = Cast<ATank>(Pawn);

		if (!ensure(possessedTank)) return;

		possessedTank->OnTankDeath.AddUniqueDynamic(this, &APlayerTankController::OnPossessedTankDeath);
	}
}

void APlayerTankController::AimTowardsCrosshair()
{
	// may not always pocess a pawn
	if (!GetPawn()) return;

	// get our tank's aiming component
	auto fireControl = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(fireControl)) return;

	// get the world location of a linetrace through the crosshair
	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation)) {
		// ask the controlled tank to aim at the location
		fireControl->AimAt(hitLocation);
	}
}

bool APlayerTankController::GetSightRayHitLocation(FVector & HitLocation) const
{
	// find the crosshair position
	int32 viewportWidth, viewportHeight;
	GetViewportSize(viewportWidth, viewportHeight);

	FVector2D screenLocation = FVector2D(viewportWidth * CrosshairLocX, viewportHeight * CrosshairLocY);

	FVector worldLoc, worldDir;
	if (DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, worldLoc, worldDir)) {
		// linetrace to find the world position we're aiming at
		FHitResult traceResult;
		auto traceStart = PlayerCameraManager->GetCameraLocation();
		auto traceEnd = traceStart + (worldDir * AimTraceRange);

		if (GetWorld()->LineTraceSingleByChannel(
				traceResult,
				traceStart,
				traceEnd,
				ECollisionChannel::ECC_Visibility)) {
			// successful trace
			HitLocation = traceResult.Location;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void APlayerTankController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s possessed tank death!"), *GetName());

	// become a spectator
	StartSpectatingOnly();
}
