// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"

#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"


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
	
	// get ref to barrel
	Barrel = FindComponentByClass<UTankBarrel>();

	// need to start with a reload
	LastFireTime = FPlatformTime::Seconds();
}

void ATank::AimAt(FVector TargetLocation)
{
	AimingComponent->AimAt(TargetLocation, MuzzleVelocity);
}

void ATank::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s FIRE command!"), *GetName());

	if (!ensure(Barrel)) return;

	bool bLoaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

	if (bLoaded) {
		// spawn projectile with muzzle location and rotation
		FName muzzleSocket("Muzzle");
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileToSpawn, Barrel->GetSocketLocation(muzzleSocket), Barrel->GetSocketRotation(muzzleSocket));

		// launch the projectile
		projectile->LaunchProjectile(MuzzleVelocity);

		LastFireTime = FPlatformTime::Seconds();
	}
}
