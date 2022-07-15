// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ASkyShip.generated.h"

UCLASS()
class HYPERION_API ASkyShip : public APawn
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* SkyShipCorpus;
	
public:
	// Sets default values for this pawn's properties
	ASkyShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
