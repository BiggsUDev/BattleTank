// Copyright BiggsUDev Ltd.

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

	SetRelativeRotation(FRotator(0, NewRotate, 0));	
}



