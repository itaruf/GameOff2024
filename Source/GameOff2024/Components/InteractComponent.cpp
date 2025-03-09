// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameOff2024/Meshes/MeshHelper.h"
#include "GameOff2024/PlayerHelpers/PlayerCollisionHelper.h"
#include "GameOff2024/PlayerHelpers/PlayerTransformHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* UInteractComponent::GetClosestActor(const FVector SpherePos,
                                            float SphereRadius,
                                            const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes,
                                            UClass* ActorClassFilter, const TArray<AActor*>& ActorsToIgnore) const
{
	if (const UWorld* World = GetWorld())
	{
		// Define the method to get the Actors
		// Here we'll use a Sphere Overlap to filter the first batch of Actors within the radius
		TArray<AActor*> Actors;
		UKismetSystemLibrary::SphereOverlapActors(World, SpherePos, SphereRadius, ObjectTypes,
		                                          ActorClassFilter, ActorsToIgnore, Actors);

		// For each of those Actors, determine which one is within the FoV and closest to where the Player is looking
		if (const UCapsuleComponent* PlayerCapsuleComponent = UPlayerCollisionHelper::GetPlayerCapsuleComponent(
			World, 0))
		{
			FVector PlayerForwardVector = PlayerCapsuleComponent->GetForwardVector();
			FVector PlayerLocation = UPlayerTransformHelpers::GetPlayerLocation(World);

			float BestAngle = 360.0f;

			AActor* ClosestActor = nullptr;

			for (const auto Candidate : Actors)
			{
				FVector CandidateLocation = Candidate->GetActorLocation();

				FVector DirectionToCandidate = UKismetMathLibrary::Normal(CandidateLocation - PlayerLocation);

				double DotProduct = UKismetMathLibrary::Dot_VectorVector(DirectionToCandidate, PlayerForwardVector);
				float AngleDegrees = UKismetMathLibrary::RadiansToDegrees(acos(DotProduct));

				if (AngleDegrees <= MaxAngle && AngleDegrees < BestAngle)
				{
					ClosestActor = Candidate;
					BestAngle = AngleDegrees;
				}
			}

			return ClosestActor;
		}
	}
	return nullptr;
}


bool UInteractComponent::IsActorInLineSight(
	const FVector StartLocation,
	const AActor* Actor,
	const TArray<TEnumAsByte<ECollisionChannel>>& ChannelsToTrace,
	const TArray<AActor*>& ActorsToIgnore) const
{
	if (const UWorld* World = GetWorld())
	{
		FHitResult Hit;

		// Build object query parameters to only trace against specified collision channels.
		FCollisionObjectQueryParams ObjectQueryParams;
		for (auto Channel : ChannelsToTrace)
		{
			ObjectQueryParams.AddObjectTypesToQuery(Channel);
		}

		// Set up additional query parameters including actors to ignore.
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActors(ActorsToIgnore);

		FVector EndLocation = UMeshHelper::GetActorMeshOrigin(Actor);

		// Perform the line trace.
		bool bHit = World->LineTraceSingleByObjectType(
			Hit,
			StartLocation,
			EndLocation,
			ObjectQueryParams,
			QueryParams
		);

		// Determine the end location for the debug trace.
		FVector HitLocation = bHit ? Hit.ImpactPoint : UMeshHelper::GetActorMeshOrigin(Actor);

		// Draw the debug line showing the trace path.
		// The line is drawn in green for 2 seconds.
		DrawDebugLine(World, StartLocation, HitLocation, FColor::Green, false, 2.0f, 0, 1.0f);

		// Optionally, draw a sphere at the impact point if something was hit.
		if (bHit)
		{
			DrawDebugSphere(World, Hit.ImpactPoint, 10.f, 12, FColor::Red, false, 2.0f);
		}

		// Return true only if the hit actor is the one we expect.
		return (bHit && Hit.GetActor() == Actor);
	}

	return false;
}
