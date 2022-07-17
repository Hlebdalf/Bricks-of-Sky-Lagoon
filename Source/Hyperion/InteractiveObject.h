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
	UStaticMeshComponent*UInteractiveMesh;
	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractiveObjectTrigger;
	UPROPERTY(Replicated)
	ACharacter* HyperionCharacter;
	UPROPERTY()
	APlayerController* OwnerPlayerController;
	UPROPERTY(Replicated)
	bool bIsControlling=false;
	
	UFUNCTION(Server, Reliable)
	void PossessToCharacter();

	UFUNCTION(Server, Unreliable)
	void SetInputDirection(float LeftRightValue,float ForwardBackValue);
	
	
public:
	AInteractiveObject();
	UPROPERTY(Replicated)
	FVector2D InputDirection = FVector2D(0,0);
	
	UFUNCTION()
	void SetInputLeftRightValue(float Value);
	UFUNCTION()
	void SetInputForwardBackValue(float Value);
	UFUNCTION(Server, Reliable)
	void SetHyperionCharacter(ACharacter* object);
	UFUNCTION()
	bool GetIsControlling();
	UFUNCTION(Server, Reliable)
	void SetIsControlling(bool how);
	
protected:
	UFUNCTION()
	void PressedFButton();
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
