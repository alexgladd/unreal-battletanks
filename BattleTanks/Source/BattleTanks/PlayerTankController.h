// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"

#include "GameFramework/PlayerController.h"
#include "PlayerTankController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
	
public:

	// Called upon spawn
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

	// Return the tank pawn that this player controls
	ATank* GetControlledTank() const;
	
private:

	// Horizontal screen location of the crosshair (0.0-1.0)
	UPROPERTY(EditAnywhere)
	float CrosshairLocX = 0.5f;

	// Vertical screen location of the crosshair (0.0-1.0)
	UPROPERTY(EditAnywhere)
	float CrosshairLocY = 0.333333f;

	// How far out should we attempt line trace for aiming
	UPROPERTY(EditAnywhere)
	float AimTraceRange = 1000000.f;

	// Move the tank barrel towards the player's crosshair
	void AimTowardsCrosshair();

	// Get the world location the player is aiming at
	bool GetSightRayHitLocation(FVector &HitLocation) const;
};
