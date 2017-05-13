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
	// Only gets called by tank player controller if the crosshair linetrace hits something
	// Otherwise the tank barrel will not be told to elevate or lower
	if (!Barrel) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("Barrel is invalid"));
		return;  
	}

	if (!Turret)
	{
		UE_LOG(LogTemp, Warning, TEXT("Turret is invalid"));
		return;
	}

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

		// Log useful info
		//auto TankName = this->GetOwner()->GetName();
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: %s Aim solution found: %s"), Time, *TankName, *AimDirection.ToString());

	}
	else
	{
		// Log useful info
		//auto TankName = this->GetOwner()->GetName();
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: %s No Aim sol"), Time, *TankName);
	}
}
