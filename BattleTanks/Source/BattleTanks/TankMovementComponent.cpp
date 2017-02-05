// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::MoveForward(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("%s forward movement request: %f"), *GetOwner()->GetName(), Throw);
}

