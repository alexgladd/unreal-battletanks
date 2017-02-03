// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

// Controls for a tank's barrel (elevation)
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Elevate the barrel towards the given relative pitch
	void Elevate(float RelativePitch);

private:

	// Maximum barrel elevation speed (degrees per second)
	UPROPERTY(EditDefaultsOnly)
	float MaxElevationSpeed = 5.f;

	// Minimum barrel elevation (degrees)
	UPROPERTY(EditDefaultsOnly)
	float MinElevation = 0.f;

	// Maximum barrel elevation (degrees)
	UPROPERTY(EditDefaultsOnly)
	float MaxElevation = 20.f;
};
