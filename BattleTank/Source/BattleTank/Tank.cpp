// Copyright BiggsUDev Ltd.

#include "BattleTank.h"
#include "TankAimingComponent.h" 
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector HitLocation)
{
	//TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::BeginPlay()
{
	// Super?

	UE_LOG(LogTemp, Warning, TEXT("BIGGS Tank.cpp BeginPlay() C++"))
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded) 
	{ 
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);		

		LastFireTime = FPlatformTime::Seconds();
	}
}

