// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

	return;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto* ControlledTank = this->GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possessing: %s"), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController failed to possess a tank"));
	}	
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation = FVector(1,1,1); // Out parameter
	
	if(GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("ScreenLocation(): %s"), *HitLocation.ToString());
	}	

	// Get world location of linetrace through crosshair
	// If it hits the landscape
		// Tell the controlled tank to aim at this point

	return;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation)
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshariXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-project" the screen position of the crosshair to a world direction	
	FVector WorldLocation;
	FVector LookDirection;

	DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		WorldLocation, 
		LookDirection
	);
	
	// Get the player view point
	auto StartLocation = PlayerCameraManager->GetCameraLocation();

	// Get a vector that is at the specified range in the direction the player is looking
	FVector VectorEnd = StartLocation + LookDirection * LineTraceRange;
	
	// Not sure what this means or why we need it
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;

	bool result = GetWorld()->LineTraceSingleByChannel(
		Hit,
		StartLocation,
		VectorEnd,
		ECollisionChannel::ECC_Visibility,
		TraceParameters
	);

	HitLocation = Hit.Location;

	return result;
}
