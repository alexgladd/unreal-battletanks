// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

// forward decls
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the tank takes damage
	float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* Instigator, AActor* Causer) override;

	// Get the current health percentage (0.0-1.0)
	UFUNCTION(BlueprintPure, Category = "Tank")
	float GetHealthPercentage() const;

	// Delegate for tank death events
	FTankDelegate OnTankDeath;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Firing)
	UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Driving)
	UTankMovementComponent* MovementComponent = nullptr;

private:

	// How much health the tank starts with
	UPROPERTY(EditDefaultsOnly, Category = "Tank")
	float StartingHealth = 100.f;

	// Current tank health
	UPROPERTY(VisibleAnywhere, Category = "Tank")
	float CurrentHealth;

};
