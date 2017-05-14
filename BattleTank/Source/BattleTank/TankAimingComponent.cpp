// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	// If we don't have a barrel or turret, log it and exit this function
	if (!Barrel) { 	UE_LOG(LogTemp, Warning, TEXT("UTankAimingComponent::Barrel is invalid"));	return; }
	if (!Turret) { 	UE_LOG(LogTemp, Warning, TEXT("UTankAimingComponent::Turret is invalid"));	return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::OnlyTraceWhileAscending
	);

	if (bHaveAimSolution)
	{
		// These two variables are used in turret and barrel aiming
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto AimAsRotator = AimDirection.Rotation();

		// MoveBarrelTowards(FVector AimDirection);
		auto BarrelRotator = Barrel->GetForwardVector().Rotation();		
		// Work-out the difference between current barrel rotation and AimDirection
		auto DeltaRotator = AimAsRotator - BarrelRotator;
		Barrel->Elevate(DeltaRotator.Pitch); 
		Turret->Rotate(DeltaRotator.Yaw);
	}
}
