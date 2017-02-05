// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

// Control the movement of a tank with a fly-by-wire system
UCLASS()
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	// Direct the tank to move forward with the given magnitude (-1.0-1.0)
	UFUNCTION(BlueprintCallable, Category = Driving)
	void MoveForward(float Throw);
	
	// Direct the tank to turn
};
