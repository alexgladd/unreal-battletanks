// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

// Controls for the tank's turret (rotation)
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Rotate the turret towards the given relative degrees
	void Rotate(float RelativeYaw);

private:

	// Maximum turret rotation speed (degrees per second)
	UPROPERTY(EditDefaultsOnly)
	float MaxRotationSpeed = 10.f;
};
