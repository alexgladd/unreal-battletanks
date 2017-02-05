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
	// get requested move direction
	auto moveDirection = MoveVelocity.GetSafeNormal();
	// get my forward
	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	//UE_LOG(LogTemp, Warning, TEXT("AI %s requested move direction: %s"), *GetOwner()->GetName(), *moveDirection.ToString());
	//DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), (GetOwner()->GetActorLocation() + (moveDirection * 1000.f)), FColor(255, 0, 0), false, -1.f, 0, 5.f);

	// dot product for 'forward' intention
	auto forwardThrow = FVector::DotProduct(moveDirection, tankForward);

	// cross product for 'turning' intention
	auto turnRightThrow = FVector::CrossProduct(tankForward, moveDirection).Z;

	//UE_LOG(LogTemp, Warning, TEXT("AI %s calculated move throws: [%f forward, %f right]"), *GetOwner()->GetName(), forwardThrow, turnRightThrow);

	// move based on the calculated throws
	MoveForward(forwardThrow);
	TurnRight(turnRightThrow);
}

