// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Command the tank to aim at the given world location
	void AimAt(FVector TargetLocation);

	// Set the reference to the tank's muzzle
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetMuzzleReference(USceneComponent* TankMuzzle);

protected:

	UTankAimingComponent* AimingComponent = nullptr;
};
