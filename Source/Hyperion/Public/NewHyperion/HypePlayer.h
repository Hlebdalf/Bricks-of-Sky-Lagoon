// by Hlebdalf

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HypePlayer.generated.h"

UCLASS()
class HYPERION_API AHypePlayer : public APawn
{
	GENERATED_BODY()

public:
	AHypePlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
