// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChangeableObject.h"
#include "Cannon.generated.h"

/**
 * 
 */
UCLASS()
class HYPERION_API ACannon : public AChangeableObject
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* UCannonMesh;

public:
	ACannon();
	virtual void Tick(float DeltaSeconds) override;
};
