// Copyright BiggsUDev Ltd.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	void BeginPlay() override;	

	virtual void Tick(float DeltaTime) override;

	// How close can AI tank get to player.
	float AcceptanceRadius = 3000;
};
