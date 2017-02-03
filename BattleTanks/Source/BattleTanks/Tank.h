// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// forward decls
class UTankAimingComponent;
class UTankBarrel;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Command the tank to aim at the given world location
	void AimAt(FVector TargetLocation);

protected:

	UTankAimingComponent* AimingComponent = nullptr;

private:
	// Muzzle speed of fired projectiles (units per second)
	UPROPERTY(EditAnywhere, Category = Firing)
	float MuzzleVelocity = 100000.f;
};
