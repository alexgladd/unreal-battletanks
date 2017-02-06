// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// forward decls
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Enumeration of fire control states
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

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

	// Fire the main gun
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Command the component to aim at the given world location
	void AimAt(FVector TargetLocation);

protected:

	// Current firing state
	UPROPERTY(BlueprintReadOnly, Category = Firing)
	EFiringState FiringState = EFiringState::Locked;

private:

	// Muzzle speed of fired projectiles (units per second)
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float MuzzleVelocity = 10000.f;

	// Time to reload the gun (seconds)
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.f;

	// Reference to projectile prototype
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	TSubclassOf<AProjectile> ProjectileToSpawn;

	// Last time the gun was fired
	double LastFireTime = 0.0;

	// Reference to the tank's barrel
	UTankBarrel* Barrel = nullptr;

	// Reference to the tank's turret
	UTankTurret* Turret = nullptr;

	// Elevate the barrel towards the given fire solution
	void RotateTowardsFireSolution(FVector FireSolution);
};
