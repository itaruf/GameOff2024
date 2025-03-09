#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MeshHelper.generated.h"

/**
 * A helper class to get mesh information from an actor.
 */
UCLASS()
class GAMEOFF2024_API UMeshHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Returns the geometric center (origin) of the first mesh component found on the actor.
	 * If no mesh component exists, returns the actor's location.
	 *
	 * @param Actor The actor to get the mesh origin from.
	 * @return The origin of the mesh or the actor's location if no mesh is found.
	 */
	UFUNCTION(BlueprintPure, Category = "Mesh")
	static FVector GetActorMeshOrigin(const AActor* Actor);
};
