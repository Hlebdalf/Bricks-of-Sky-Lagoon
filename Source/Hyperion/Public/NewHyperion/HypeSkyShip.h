// by Hlebdalf

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HypeSkyShip.generated.h"

UCLASS()
class HYPERION_API AHypeSkyShip : public APawn
{
	GENERATED_BODY()

public:
	AHypeSkyShip();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
