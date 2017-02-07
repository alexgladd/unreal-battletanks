// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.f, 1.f);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	// drive the tracks with the requested throttle settings
	DriveTrack();
	// reset throttle to accumulate throttle for next frame
	CurrentThrottle = 0.f;

	// apply a sideways counter force to prevent side-slipping
	ApplySidewaysForce();
}

void UTankTrack::DriveTrack()
{
	// calculate force params
	FVector forceApplied = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
	FVector forceLocation = GetComponentLocation();

	// apply the force to the tank body
	auto rootTank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	rootTank->AddForceAtLocation(forceApplied, forceLocation);
}

void UTankTrack::ApplySidewaysForce()
{
	// how fast are we sliding to the right
	auto slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	// calculated the required acceleration to cancel all of this speed in this frame
	auto correctionAccel = -slippageSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();

	// apply the required force to acheive the acceleration
	auto tank = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = tank->GetMass() * correctionAccel / 2.f; // two tracks!
	tank->AddForce(correctionForce);
}

