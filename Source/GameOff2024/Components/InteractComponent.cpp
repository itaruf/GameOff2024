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
                                            UClass* ActorClassFilter,
                                            const TArray<AActor*>& ActorsToIgnore) const
{
	if (const UWorld* World = GetWorld())
	{
		// Gather all overlapping actors within the sphere.
		TArray<AActor*> Actors;
		UKismetSystemLibrary::SphereOverlapActors(World, SpherePos, SphereRadius, ObjectTypes,
		                                          ActorClassFilter, ActorsToIgnore, Actors);

		// Get the player's capsule component and associated location/forward vector.
		if (const UCapsuleComponent* PlayerCapsuleComponent = UPlayerCollisionHelper::GetPlayerCapsuleComponent(World, 0))
		{
			FVector PlayerForwardVector = PlayerCapsuleComponent->GetForwardVector();
			FVector PlayerLocation = UPlayerTransformHelpers::GetPlayerLocation(World);

			// Define a threshold: if a candidate is this close, ignore the angle test.
			const float CloseDistanceThreshold = 100.0f; // Adjust as needed.
			const float CloseDistanceThresholdSq = FMath::Square(CloseDistanceThreshold);

			float BestAngle = 360.0f;
			float BestDistanceSq = FLT_MAX;
			AActor* ClosestActor = nullptr;

			for (const AActor* Candidate : Actors)
			{
				FVector CandidateLocation = Candidate->GetActorLocation();
				float DistanceSq = FVector::DistSquared(CandidateLocation, PlayerLocation);

				// If candidate is extremely close, select it based on distance.
				if (DistanceSq < CloseDistanceThresholdSq)
				{
					if (DistanceSq < BestDistanceSq)
					{
						BestDistanceSq = DistanceSq;
						ClosestActor = const_cast<AActor*>(Candidate);
					}
				}
				else
				{
					// Compute direction to candidate using safe normalization.
					FVector DirectionToCandidate = (CandidateLocation - PlayerLocation).GetSafeNormal();
					float DotProduct = FVector::DotProduct(DirectionToCandidate, PlayerForwardVector);
					// Clamp dot product to avoid NaN due to floating point error.
					DotProduct = FMath::Clamp(DotProduct, -1.0f, 1.0f);
					float AngleDegrees = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

					// Check if the candidate is within the maximum angle and if it has the smallest angle so far.
					if (AngleDegrees <= MaxAngle && AngleDegrees < BestAngle)
					{
						BestAngle = AngleDegrees;
						ClosestActor = const_cast<AActor*>(Candidate);
					}
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
