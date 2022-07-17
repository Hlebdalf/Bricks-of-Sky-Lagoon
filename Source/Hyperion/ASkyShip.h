// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Pawn.h"
#include "ASkyShip.generated.h"

UCLASS()
class HYPERION_API ASkyShip : public APawn
{
	GENERATED_BODY()
	
	UPROPERTY()
	UStaticMeshComponent* SkyShipCorpus;
	/*UPROPERTY(EditInstanceOnly)
	UChildActorComponent* AWheel;*/
	UPROPERTY(EditDefaultsOnly)
	UArrowComponent* ForwardArrow;
	UPROPERTY(EditDefaultsOnly)
	UArrowComponent* BackArrow;
	UPROPERTY(EditDefaultsOnly)
	UArrowComponent* LeftArrow;
	UPROPERTY(EditDefaultsOnly)
	UArrowComponent* RightArrow;

	UPROPERTY(Replicated)
	float SkyShipTorque = 0;
	
	
public:
	ASkyShip();
	UFUNCTION(Server, Unreliable)
	void SetSkyShipTorque(float Value);
	

protected:
	UPROPERTY(EditInstanceOnly, Category="MovementSettings")
	float AngDamping = 20;
	UPROPERTY(EditInstanceOnly, Category="MovementSettings")
	float LinDamping = 10;
	UPROPERTY(EditInstanceOnly, Category="MovementSettings")
	float UpForceMP = 1;
	UPROPERTY(EditInstanceOnly, Category="MovementSettings")
	float SpeedMP = 1;
	UPROPERTY(EditInstanceOnly, Category="MovementSettings")
	float SkyLevel = 0;
	
	virtual void BeginPlay() override;
	
	void UpdatePhysics();
	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
