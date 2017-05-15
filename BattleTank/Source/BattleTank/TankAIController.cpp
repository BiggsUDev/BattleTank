// Copyright BiggsUDev Ltd.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get and make sure we have a controlled tank
	ATank* ControlledTank = Cast<ATank>(GetPawn());	
	if (!ControlledTank) { UE_LOG(LogTemp, Warning, TEXT("AIController has no ControlledTank"));  return; } 


	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank) 
	{ 
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		ControlledTank->Fire();
	}
	else { UE_LOG(LogTemp, Warning, TEXT("AIController + PlayerTank")); }

}