// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

	
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController cannot find player tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *(PlayerTank->GetName()))
	}
}

//void ATankAIController::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//		AimTowardCrosshair();
//}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn)
	{
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

//void ATankAIController::AimTowardCrosshair()
//{
//	if (!GetControlledTank())
//	{
//		return;
//	}
//
//	FVector HitLocation; //Out parameter
//	if (GetSightRayHitLocation(HitLocation)) //Has "side-effect", is going to line trace
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *(HitLocation.ToString()))
//		//TODO Tell controlled tank to aim at this point
//	}
//}

////Get world location of linetrace through crosshair, true if hits landscape
//bool ATankAIController::GetSightRayHitLocation(FVector& OutHitLocation) const
//{
//	//Find the crosshair position
//	int32 ViewPortSizeX, ViewPortSizeY;
//	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
//
//	//"De-project" the screen position of the crosshair to a world direction
//	//Line-trace along that look direction, and see what we hit (up to max range)
//	return true;
//}
