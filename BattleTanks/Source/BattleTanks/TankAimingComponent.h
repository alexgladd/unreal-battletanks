// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// forward decls
class UTankBarrel;
class UTankTurret;

// Controls the aiming of the turret and barrel
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Setup the aiming system with turret and barrel references
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetupAiming(UTankTurret* TankTurret, UTankBarrel* TankBarrel);

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Command the component to aim at the given world location
	void AimAt(FVector TargetLocation, float ProjectileSpeed);

	// Set the reference to the tank's barrel
	void SetBarrelReference(UTankBarrel* TankBarrel);

private:
	// Reference to the tank's barrel
	UTankBarrel* Barrel = nullptr;

	// Reference to the tank's turret
	UTankTurret* Turret = nullptr;

	// Elevate the barrel towards the given fire solution
	void RotateTowardsFireSolution(FVector FireSolution);
};
