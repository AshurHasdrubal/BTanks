// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BTANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	ATank* GetControlledTank() const;

	void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	//Start the tank moving tha barrel so that a shot would it where 
	//the crosshair intersects the world
	void AimTowardsCrosshair();

	//return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;


	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;


	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.f;
};
