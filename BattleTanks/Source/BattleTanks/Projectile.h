// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Launch the projectile at the given speed
	void LaunchProjectile(float Speed);

protected:
	
	// Projectile movement
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComponent = nullptr;

	// Collision mesh for the projectile
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CollisionMesh = nullptr;

	// Particle system for generating the launch blast
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* LaunchBlast = nullptr;

	// Particle system for generating the impact blast
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ImpactBlast = nullptr;

	// Particle system for generating the impact blast
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ImpactForce = nullptr;

private:

	// How long to wait before destroying projectile after impact with something
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float DestroyDelay = 10.f;

	// How much damage the projectile does
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float ImpactDamage = 20.f;

	// Detect collisions to know when we should fire the impact particle effect
	UFUNCTION()
	void OnImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult &Hit);

	// Called by a timer to destroy the projectile
	void OnTimerFire();
	
};
