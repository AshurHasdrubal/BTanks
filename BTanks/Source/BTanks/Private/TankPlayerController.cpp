	// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is not possesing tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is possesing: %s"), *ControlledTank->GetName());
		ControlledTank->SetActorScale3D(FVector(1.25f, 1.25f, 1.25f));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
		Super::Tick(DeltaTime);
		AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;
	
	FVector OutHitLocation; // OUT parameter

	if (GetSightRayHitLocation(OutHitLocation))  // Has "side-effect", is going to line trace
	{
		GetControlledTank()->AimAt(OutHitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation); // section 4, lecture 134 08:00

	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//line trace along direction (up to maximum range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{

	FVector CameraWorldLocation; // to be discarded

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
		
	//sect 4, lect 136
	if (GetWorld()->LineTraceSingleByChannel(                                  
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)

	)

	{
		HitLocation = HitResult.Location;
		return true;
	}

	return false;
}

