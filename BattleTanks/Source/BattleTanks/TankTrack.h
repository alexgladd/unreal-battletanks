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

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Set the throttle for the track
	UFUNCTION(BlueprintCallable, Category = Driving)
	void SetThrottle(float Throttle);
	
private:

	// Maximum driving force of the track in newtons
	UPROPERTY(EditDefaultsOnly, Category = Driving)
	float MaxDrivingForce = 400000.f;
};
