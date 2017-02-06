// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"

#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankAimingComponent::SetupAiming(UTankTurret * TankTurret, UTankBarrel * TankBarrel)
{
	Turret = TankTurret;
	Barrel = TankBarrel;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) return;

	if (FiringState != EFiringState::Reloading) {
		// spawn projectile with muzzle location and rotation
		FName muzzleSocket("Muzzle");
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileToSpawn, Barrel->GetSocketLocation(muzzleSocket), Barrel->GetSocketRotation(muzzleSocket));

		// launch the projectile
		projectile->LaunchProjectile(MuzzleVelocity);

		// start reloading
		FiringState = EFiringState::Reloading;
		LastFireTime = FPlatformTime::Seconds();
	}
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// force tanks to start with a reload
	FiringState = EFiringState::Reloading;
	LastFireTime = FPlatformTime::Seconds();

	// init muzzle aim
	if (ensure(Barrel)) {
		RequestedMuzzleAim = Barrel->GetForwardVector().GetSafeNormal();
	}
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if ((FPlatformTime::Seconds() - LastFireTime) <= ReloadTime) {
		FiringState = EFiringState::Reloading;
	}
	else if (!RequestedMuzzleAim.Equals(Barrel->GetForwardVector(), 0.01f)) {
		FiringState = EFiringState::Aiming;
	}
	else {
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector TargetLocation)
{
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s aiming at location %s from %s"), *GetOwner()->GetName(), *TargetLocation.ToString(), *Muzzle->GetComponentLocation().ToString());

	if (!ensure(Barrel && Turret)) return;

	FVector firingSolution;

	if (UGameplayStatics::SuggestProjectileVelocity(this, firingSolution, Barrel->GetSocketLocation(FName("Muzzle")), TargetLocation, MuzzleVelocity, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		RequestedMuzzleAim = firingSolution.GetSafeNormal();
		RotateTowardsFireSolution(RequestedMuzzleAim);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tank %s unable to calculate firing solution"), *GetOwner()->GetName());
	}
}

void UTankAimingComponent::RotateTowardsFireSolution(FVector FireSolution)
{
	auto muzzleRot = Barrel->GetForwardVector().Rotation();
	auto solutionRot = FireSolution.Rotation();
	auto deltaRot = solutionRot - muzzleRot;

	// elevate towards our delta pitch
	Barrel->Elevate(deltaRot.Pitch);
	
	// rotate towards our delta yaw (always go the short way)
	(FMath::Abs<float>(deltaRot.Yaw) < 180)? Turret->Rotate(deltaRot.Yaw) : Turret->Rotate(-deltaRot.Yaw);
}

