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
	
public:
	// Sets default values for this pawn's properties
	AInteractiveObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	

public:	
	UFUNCTION()	
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
					  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
