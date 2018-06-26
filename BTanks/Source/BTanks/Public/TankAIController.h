// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BTANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	

		ATank* GetControlledTank() const;

		virtual void BeginPlay() override;
		virtual void Tick(float DeltaSeconds) override;

		ATank* GetPlayerTank() const;
		

		
	
};
