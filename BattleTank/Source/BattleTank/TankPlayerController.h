// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	virtual ATank* GetControlledTank() const;

private:
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.f;

	void BeginPlay() override;

	void Tick(float DeltaTime) override;
	
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation);



};
