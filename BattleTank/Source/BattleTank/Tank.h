// Copyright BiggsUDev Ltd.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
	
private:	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; //  https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 100000.f; // TODO find sensible default

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	void BeginPlay() override;

	// Sets default values for this pawn's properties
	ATank();	

	UTankBarrel* Barrel = nullptr;
	
	double LastFireTime = 0;
};
