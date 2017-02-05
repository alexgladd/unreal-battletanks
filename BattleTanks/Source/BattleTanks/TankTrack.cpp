// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s setting throttle to %f"), *GetName(), Throttle);

	// calculate force params
	FVector forceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	FVector forceLocation = GetComponentLocation();

	// apply the force to the tank body
	auto rootTank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	rootTank->AddForceAtLocation(forceApplied, forceLocation);
}

