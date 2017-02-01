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

	// Move the tank barrel towards the player's crosshair
	void AimTowardsCrosshair();
};
