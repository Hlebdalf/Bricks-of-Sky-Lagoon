// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "InteractiveObject.generated.h"

UCLASS()
class HYPERION_API AInteractiveObject : public APawn
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractiveObjectTrigger;
	UPROPERTY(Replicated)
	APawn* HyperionPlayer;

	UPROPERTY(Replicated)
	bool bIsControlling = false;

	UFUNCTION(Server, Unreliable)
	void SetInputDirection(float LeftRightValue, float ForwardBackValue);


public:
	AInteractiveObject();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(Server, Reliable)
	void SetInputRightValue(float Value);
	UFUNCTION(Server, Unreliable)
	void SetInputForwardValue(float Value);
	UFUNCTION(Server, Reliable)
	void SetHyperionPlayer(APawn* object);
	UFUNCTION()
	bool GetIsControlling();
	UFUNCTION(Server, Reliable)
	void SetIsControlling(bool how);

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* UInteractiveMesh;
	UPROPERTY(Replicated)
	FVector2D InputDirection = FVector2D(0, 0);
};
