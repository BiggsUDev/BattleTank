// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

// Relative speed
void UTankTurret::Rotate(float RelativeSpeed)
{
	//Move the barrel the right amount this frame
	//Given a max elevation speed, and the time frame
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotateChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;


	auto NewRotate = RelativeRotation.Yaw + RotateChange;
	UE_LOG(LogTemp, Warning, TEXT("RotateChange %f"), RotateChange);
	//NewRotate = FMath::Clamp<float>(NewRotate, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(0, NewRotate, 0));

	//auto TankName = this->GetOwner()->GetName();
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: %s Aim solution found: %f"), Time, *TankName, *NewRotate);
	
}



