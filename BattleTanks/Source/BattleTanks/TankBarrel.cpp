// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativePitch)
{
	// clamp down to a elevation "direction" which will also modify our speed below one degree
	float rotModifier = FMath::Clamp<float>(RelativePitch, -1.f, 1.f);

	// calculate the rotation step
	float elevationStep = rotModifier * MaxElevationSpeed * GetWorld()->DeltaTimeSeconds;
	float nextElevation = FMath::Clamp<float>(RelativeRotation.Pitch + elevationStep, MinElevation, MaxElevation);

	// change elevation
	SetRelativeRotation(FRotator(nextElevation, 0.f, 0.f));
}

