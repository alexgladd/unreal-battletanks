// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Command the component to aim at the given world location
	void AimAt(FVector TargetLocation);

	// Set the reference to the tank's muzzle
	void SetMuzzleReference(USceneComponent* TankMuzzle);

private:
	// Reference to the tank's muzzle
	USceneComponent* Muzzle = nullptr;
};
