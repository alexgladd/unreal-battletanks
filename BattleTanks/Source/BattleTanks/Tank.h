// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// forward decls
class UTankAimingComponent;
class UTankMovementComponent;
class UTankBarrel;
class AProjectile;

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

	// Fire the main gun
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:

	UPROPERTY(BlueprintReadOnly, Category = Firing)
	UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = Driving)
	UTankMovementComponent* MovementComponent = nullptr;

private:
	// Muzzle speed of fired projectiles (units per second)
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float MuzzleVelocity = 100000.f;

	// Time to reload the gun (seconds)
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.f;

	// Reference to projectile prototype
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileToSpawn;

	UTankBarrel* Barrel;

	double LastFireTime = 0.0;
};
