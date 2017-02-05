// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"

#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetupAiming(UTankTurret * TankTurret, UTankBarrel * TankBarrel)
{
	Turret = TankTurret;
	Barrel = TankBarrel;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::AimAt(FVector TargetLocation, float ProjectileSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s aiming at location %s from %s"), *GetOwner()->GetName(), *TargetLocation.ToString(), *Muzzle->GetComponentLocation().ToString());

	if (!ensure(Barrel && Turret)) return;

	FVector firingSolution;

	if (UGameplayStatics::SuggestProjectileVelocity(this, firingSolution, Barrel->GetSocketLocation(FName("Muzzle")), TargetLocation, ProjectileSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto muzzleAim = firingSolution.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Tank %s calculated muzzle aim %s"), *GetOwner()->GetName(), *muzzleAim.ToString());
		RotateTowardsFireSolution(muzzleAim);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tank %s unable to calculate firing solution"), *GetOwner()->GetName());
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * TankBarrel)
{
	Barrel = TankBarrel;
}

void UTankAimingComponent::RotateTowardsFireSolution(FVector FireSolution)
{
	auto muzzleRot = Barrel->GetForwardVector().Rotation();
	auto solutionRot = FireSolution.Rotation();
	auto deltaRot = solutionRot - muzzleRot;

	//UE_LOG(LogTemp, Warning, TEXT("Tank %s delta rotation for fire solution: %s"), *GetOwner()->GetName(), *deltaRot.ToString());

	// elevate towards our delta pitch
	Barrel->Elevate(deltaRot.Pitch);
	
	// rotate towards our delta yaw (always go the short way)
	(FMath::Abs<float>(deltaRot.Yaw) < 180)? Turret->Rotate(deltaRot.Yaw) : Turret->Rotate(-deltaRot.Yaw);
}

