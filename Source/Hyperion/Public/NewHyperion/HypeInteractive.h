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
	AHypeInteractive();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
