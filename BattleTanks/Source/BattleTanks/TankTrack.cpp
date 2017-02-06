// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	// how fast are we sliding to the right
	auto slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	// calculated the required acceleration to cancel all of this speed in this frame
	auto correctionAccel = -slippageSpeed / DeltaTime * GetRightVector();

	// apply the required force to acheive the acceleration
	auto tank = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = tank->GetMass() * correctionAccel / 2.f; // two tracks!
	tank->AddForce(correctionForce);
}

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

