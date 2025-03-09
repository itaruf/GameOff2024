#include "MeshHelper.h"
#include "Components/MeshComponent.h"
#include "GameFramework/Actor.h"

FVector UMeshHelper::GetActorMeshOrigin(const AActor* Actor)
{
	if (!Actor)
	{
		return FVector::ZeroVector;
	}

	// Find the first mesh component (works for both static and skeletal meshes)
	UMeshComponent* MeshComp = Actor->FindComponentByClass<UMeshComponent>();
	if (MeshComp)
	{
		// Calculate the bounds of the mesh, which gives us the geometric center.
		FBoxSphereBounds Bounds = MeshComp->CalcBounds(MeshComp->GetComponentTransform());
		return Bounds.Origin;
	}

	// Fallback: return the actor's location if no mesh component is found.
	return Actor->GetActorLocation();
}
