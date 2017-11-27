// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel)
	{
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,												// const UObject							*WorldContextObject		  
		OutLaunchVelocity,									// FVector									&TossVelocity
		StartLocation,										// FVector									StartLocation
		HitLocation,										// FVector									EndLocation 
		LaunchSpeed,										// float									TossSpeed 
															// bool										bHighArc					default value = false,    
															// float									CollisionRadius				default value = 0,
															// float									OverrideGravityZ			default value = 0,
		ESuggestProjVelocityTraceOption::DoNotTrace			// ESuggestProjVelocityTraceOption::Type	TraceOption					default value = ESuggestProjVelocityTraceOption::TraceFullPath
															// const FCollisionResponseParams			ResponseParam				default value = FCollisionResponseParams::DefaultResponse
															// const TArray < AActor * >				&ActorsToIgnore				default value = TArray<...>()
															// bool										bDrawDebug					default value = false
	);

	//Calculate teh OutLaunchVelocity
	if (bHaveAimSolution) //Calculate the OutLaunchVelocity
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
	}
	// If no solution found do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out difference between current reaction, and AimDreiction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(5); //TODO remove magic number
}

