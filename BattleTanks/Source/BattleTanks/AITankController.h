// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"

#include "AIController.h"
#include "AITankController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API AAITankController : public AAIController
{
	GENERATED_BODY()
	
public:

	// Called upon spawn
	void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Return the tank pawn that this player controls
	ATank* GetControlledTank() const;

private:

	// Find the player's tank
	ATank* GetPlayerTank() const;

	// Aim towards the player's tank
	void AimTowardsPlayer();

};
