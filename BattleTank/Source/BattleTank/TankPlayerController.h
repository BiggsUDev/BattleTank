// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	float CrosshariXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void AimTowardsCrosshair();

	virtual bool GetSightRayHitLocation(FVector& HitLocation);

public:
	virtual ATank* GetControlledTank() const;

};
