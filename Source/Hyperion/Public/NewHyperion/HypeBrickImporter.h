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
	// Sets default values for this actor's properties
	AHypeBrickImporter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintImplementableEvent)
	void DamageShip(FVector location, UPrimitiveComponent* OtherComp);

};
