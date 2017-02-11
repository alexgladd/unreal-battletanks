// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"

#include "TankAimingComponent.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
	MovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MovementComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	// setup health
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * Instigator, AActor * Causer)
{
	auto damageToApply = FMath::Clamp<float>(FMath::RoundToFloat(DamageAmount), 0.f, CurrentHealth);

	CurrentHealth -= damageToApply;

	// broadcast if dead
	if (CurrentHealth <= 0.f) {
		OnTankDeath.Broadcast();
	}

	return damageToApply;
}

float ATank::GetHealthPercentage() const
{
	return CurrentHealth / StartingHealth;
}
