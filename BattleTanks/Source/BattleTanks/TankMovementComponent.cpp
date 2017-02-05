// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankMovementComponent.h"

#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTankTrack, UTankTrack* RightTankTrack)
{
	if (!LeftTankTrack || !RightTankTrack) {
		UE_LOG(LogTemp, Error, TEXT("Initialization failure for tank tracks on %s"), *GetOwner()->GetName());
	}
	else {
		LeftTrack = LeftTankTrack;
		RightTrack = RightTankTrack;
	}
}

void UTankMovementComponent::MoveForward(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s forward movement request: %f"), *GetOwner()->GetName(), Throw);

	// throttle up both tracks
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::TurnRight(float Throw)
{
	// throttle tracks in opposite directions
	RightTrack->SetThrottle(-Throw);
	LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// get relative direction
	auto relativeMove = (MoveVelocity.GetSafeNormal() - GetOwner()->GetActorForwardVector()).GetSafeNormal();

	// TODO figure this out

	UE_LOG(LogTemp, Warning, TEXT("%s got forward direction: %s"), *GetOwner()->GetName(), *GetOwner()->GetActorForwardVector().ToString());
	UE_LOG(LogTemp, Warning, TEXT("%s got relative move direction: %s"), *GetOwner()->GetName(), *relativeMove.ToString());

	// move based on directions
	MoveForward(relativeMove.X);
	TurnRight(relativeMove.Y);
}

