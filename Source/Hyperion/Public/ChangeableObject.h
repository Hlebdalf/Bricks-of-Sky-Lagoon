// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject.h"
#include "Camera/CameraComponent.h"
#include "ChangeableObject.generated.h"

/**
 * 
 */
UCLASS()
class HYPERION_API AChangeableObject : public AInteractiveObject
{
	GENERATED_BODY()
	
	UFUNCTION()
	void UpdateValue();
public:
	AChangeableObject();
protected:
	UPROPERTY(EditAnywhere)
	UCameraComponent* ChangeableObjectCamera;
	UPROPERTY(EditAnywhere, Category="ChangeableSettings")
	FVector2D DirectionThresholdFloor = FVector2D(0, 0);
	UPROPERTY(EditAnywhere,Category="ChangeableSettings")
	FVector2D DirectionThresholdRoof = FVector2D(0, 0);
	UPROPERTY(EditAnywhere,Category="ChangeableSettings")
	FVector2D DirectionMP = FVector2D(0, 0);
	UPROPERTY(EditAnywhere,Category="ChangeableSettings")
	FVector2D ValueMP = FVector2D(0, 0);
	UPROPERTY(BlueprintReadOnly)
	FVector2D Value = FVector2D(0, 0);
public:
	virtual void Tick(float DeltaTime) override;
};
