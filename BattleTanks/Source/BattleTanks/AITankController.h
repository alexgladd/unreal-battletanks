// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AITankController.generated.h"

// forward decls
class ATank;

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

};
