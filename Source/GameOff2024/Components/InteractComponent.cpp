// Copyright 2024. All Rights Reserved.

#include "InteractComponent.h"

// Unreal includes
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Local includes
#include "GameOff2024/PlayerHelpers/PlayerCharacterHelpers.h"
#include "GameOff2024/PlayerHelpers/PlayerCollisionHelper.h"
#include "GameOff2024/PlayerHelpers/PlayerTransformHelpers.h"


UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Potential expansions or debugging code can go here
}

AActor* UInteractComponent::GetClosestActor(
	const FVector SpherePos,
	float SphereRadius,
	const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes,
	UClass* ActorClassFilter,
	const TArray<AActor*>& ActorsToIgnore
) const
{
	if (!GetWorld())
	{
		return nullptr;
	}

	// Step 1: Overlap for an initial batch of nearby Actors within the given radius.
	TArray<AActor*> OverlappedActors;
	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		SpherePos,
		SphereRadius,
		ObjectTypes,
		ActorClassFilter,
		ActorsToIgnore,
		OverlappedActors
	);

	// Step 2: If no Player capsule is found, we can't proceed with angle checks.
	const UCapsuleComponent* PlayerCapsule = UPlayerCollisionHelper::GetPlayerCapsuleComponent(GetWorld(), /*PlayerIndex=*/0);
	if (!PlayerCapsule)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInteractComponent::GetClosestActor - No valid PlayerCapsule found!"));
		return nullptr;
	}

	// Gather references for angle calculations.
	const FVector PlayerForward = PlayerCapsule->GetForwardVector();
	const FVector PlayerLocation = UPlayerTransformHelpers::GetPlayerLocation(GetWorld());

	float NarrowestAngle = 360.0f;
	AActor* BestActor = nullptr;

	for (AActor* Candidate : OverlappedActors)
	{
		if (!Candidate)
		{
			continue;
		}
		const FVector DirectionToCandidate = (Candidate->GetActorLocation() - PlayerLocation).GetSafeNormal();
		const float DotProduct = FVector::DotProduct(DirectionToCandidate, PlayerForward);

		// Dot -> angle
		// clamp to avoid domain errors in FMath::Acos
		const float ClampedDot = FMath::Clamp(DotProduct, -1.0f, 1.0f);
		const float AngleDegrees = FMath::RadiansToDegrees(FMath::Acos(ClampedDot));

		if (AngleDegrees <= MaxAngle && AngleDegrees < NarrowestAngle)
		{
			BestActor = Candidate;
			NarrowestAngle = AngleDegrees;
		}
	}

	return BestActor;
}

bool UInteractComponent::IsActorInLineSight(
	const FVector StartLocation,
	const AActor* Actor,
	FName ProfileName,
	const TArray<AActor*>& ActorsToIgnore
) const
{
	if (!GetWorld() || !Actor)
	{
		return false;
	}

	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingleByProfile(
		GetWorld(),
		StartLocation,
		Actor->GetActorLocation(),
		ProfileName,
		/*bTraceComplex=*/true,
		ActorsToIgnore,
		/*DrawDebugType=*/EDrawDebugTrace::ForDuration,
		HitResult,
		/*bIgnoreSelf=*/true
	);

	return (HitResult.GetActor() == Actor);
}

