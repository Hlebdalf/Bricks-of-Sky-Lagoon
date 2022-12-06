// by Hlebdalf

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HypeBrickImporter.generated.h"

UCLASS()
class HYPERION_API AHypeBrickImporter : public AActor
{
	GENERATED_BODY()
	
public:	
	AHypeBrickImporter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintImplementableEvent)
	void DamageShip(FVector location, const TArray<UPrimitiveComponent*>& CollectedComponents);
};
