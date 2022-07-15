// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject.h"
#include "ChangableObject.generated.h"

UCLASS()
class HYPERION_API AChangableObject : public AInteractiveObject
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category="ChangeSettings")
	FVector2D Direction;
	UPROPERTY(VisibleAnywhere, Category="ChangeSettings")
	FVector2D Value;
	UPROPERTY(EditAnywhere, Category="ChangeSettings")
	FVector2D TresholdFloor;
	UPROPERTY(EditAnywhere, Category="ChangeSettings")
	FVector2D TresholdRoof;

protected:
	float DirectionMP;
	float ValueMP;
};
