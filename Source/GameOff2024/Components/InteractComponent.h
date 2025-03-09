// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), DisplayName="InteractComponent")
class GAMEOFF2024_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Interact", DisplayName="Get Closest Actor")
	virtual AActor* GetClosestActor(FVector SpherePos, float SphereRadius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, UClass*
	                                ActorClassFilter, const TArray<AActor*>& ActorsToIgnore) const;

	UFUNCTION(BlueprintCallable, Category="Interact", DisplayName="Is Actor In Line Sight")
	virtual bool IsActorInLineSight(FVector StartLocation, const AActor* Actor, const TArray<TEnumAsByte<ECollisionChannel>>& ChannelsToTrace, const TArray<AActor*>& ActorsToIgnore) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	float MaxAngle = 75.f;
};
