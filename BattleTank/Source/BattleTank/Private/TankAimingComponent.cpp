// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel)
	{
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	//Calculate teh OutLaunchVelocity

	if (UGameplayStatics::SuggestProjectileVelocity
			(
				this,							// const UObject *WorldContextObject
				OutLaunchVelocity,				// FVector		 &TossVelocity
				StartLocation,					// FVector		 StartLocation
				HitLocation,					// FVector		 EndLocation 
				LaunchSpeed,						// float		 TossSpeed 
				false,                          // bool			 bHighArc
				0,								// float		 CollisionRadius
				0,								// float		 OverrideGravityZ
				ESuggestProjVelocityTraceOption::DoNotTrace    // ESuggestProjVelocityTraceOption::Type	TraceOption
												// const FCollisionResponseParams			ResponseParam
												// const TArray < AActor * >				&ActorsToIgnore
				    						    // bool			 bDrawDebug
			)
		) //Calculate the OutLaunchVelocity
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *TankName, *(AimDirection.ToString()));
	}
	// If no solution found do nothing
}

