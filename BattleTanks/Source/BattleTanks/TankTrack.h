// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

// Control a tank's track
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	// Constructor
	UTankTrack();

	// Called at startup
	void BeginPlay() override;
	
	// Set the throttle for the track
	UFUNCTION(BlueprintCallable, Category = Driving)
	void SetThrottle(float Throttle);
	
private:

	// Maximum driving force of the track in newtons
	UPROPERTY(EditDefaultsOnly, Category = Driving)
	float MaxDrivingForce = 400000.f;

	// Track throttle setting
	float CurrentThrottle = 0.f;

	// Detect collisions with the ground to know when we should apply force
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult &Hit);

	// Drive the track based on throttle setting
	void DriveTrack();

	// Counteract side slipping
	void ApplySidewaysForce();
};
