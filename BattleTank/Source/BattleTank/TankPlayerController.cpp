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
	// "De-project" the screen position of the crosshair to a world direction
	// Line-trace along that look direction, and see what we hit (up to some max range)

	//FVector PlayerViewPointLocation;
	//FRotator PlayerViewPointRotation;
	//GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	//
	//FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	//UE_LOG(LogTemp, Warning, TEXT("PlayerViewPointLocation: %s"), *PlayerViewPointLocation.ToString());

	//FHitResult Hit;
	//GetWorld()->LineTraceSingleByChannel(
	//	Hit,
	//	PlayerViewPointLocation,
	//	GetPlayerViewPointReach(),
	//	ECollisionChannel::ECC_WorldStatic,
	//	TraceParameters
	//);

	//if (Hit.GetNumBlockingHits > 0)
	//{
	//	HitLocation = Hit.Location;

	HitLocation.X = ScreenLocation().X;
	HitLocation.Y = ScreenLocation().Y;

	//	return true;
	//}
	//else
	//{
	//	return false;
	//}

	return true;

}

FVector ATankPlayerController::GetPlayerViewPointReach() const
{
	/// Get the player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * 1000.f;
}

FVector2D ATankPlayerController::ScreenLocation() const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);	
	return FVector2D(ViewportSizeX * CrosshariXLocation, ViewportSizeY * CrosshairYLocation);
}



