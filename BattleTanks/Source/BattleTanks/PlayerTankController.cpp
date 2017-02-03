// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "PlayerTankController.h"

#include "Tank.h"


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

	AimTowardsCrosshair();
}

ATank* APlayerTankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void APlayerTankController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;

	// get the world location of a linetrace through the crosshair
	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation)) {
		// ask the controlled tank to aim at the location
		GetControlledTank()->AimAt(hitLocation);
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
