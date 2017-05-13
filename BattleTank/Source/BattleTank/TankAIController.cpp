// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	//if (ControlledTank)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *ControlledTank->GetName());
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("AIController failed to find tank"));
	//}

	auto* PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found PlayerTank: %s"), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController failed to find PlayerTank"));
	}

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerTank() const
{
	auto TankPlayer = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());

	return TankPlayer->GetControlledTank();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetPlayerTank()) { return; }	

	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

	return;
}