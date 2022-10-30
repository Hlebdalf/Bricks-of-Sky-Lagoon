// by Hlebdalf

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HypeInteractive.generated.h"

UCLASS()
class HYPERION_API AHypeInteractive : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHypeInteractive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
