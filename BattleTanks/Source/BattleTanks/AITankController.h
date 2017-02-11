// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AITankController.generated.h"


// An AI controlled tank
UCLASS()
class BATTLETANKS_API AAITankController : public AAIController
{
	GENERATED_BODY()
	
public:

	// Called upon spawn
	void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called when this controller posesses a pawn
	void SetPawn(APawn* Pawn) override;

protected:

	// How close should the AI try to get to the target (units)
	UPROPERTY(EditDefaultsOnly, Category = AI)
	float ApproachDistance = 8000.f;

private:

	// Called by delegate when possessed tank dies
	UFUNCTION()
	void OnPossessedTankDeath();

};
