// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeYaw)
{
	// clamp down to a rotation "direction" which will also modify our speed below one degree
	float rotModifier = FMath::Clamp<float>(RelativeYaw, -1.f, 1.f);

	// calculate the rotation step
	float rotationStep = rotModifier * MaxRotationSpeed * GetWorld()->DeltaTimeSeconds;
	float nextRotation = RelativeRotation.Yaw + rotationStep;

	// change elevation
	SetRelativeRotation(FRotator(0.f, nextRotation, 0.f));
}

