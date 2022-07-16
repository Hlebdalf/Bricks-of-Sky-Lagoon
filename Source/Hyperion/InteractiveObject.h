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
	/*UPROPERTY(Replicated)
	bool bIsControlling=false;*/
	
	UFUNCTION(Server, Reliable)
	void SetHyperionCharacter(ACharacter* object);
	UFUNCTION(Server, Reliable)
	void PossessToCharacter();
	
	
public:
	AInteractiveObject();
	/*UFUNCTION()
	bool GetIsControlling();
	UFUNCTION(NetMulticast, Reliable)
	void SetIsControlling(bool how);*/
	
protected:
	UFUNCTION()
	void PressedFButton();
	virtual void BeginPlay() override;

public:
	UFUNCTION()	
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
					  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){};
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
