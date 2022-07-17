// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShipboardChangeableObject.h"
#include "ShipWheel.generated.h"

/**
 * 
 */
UCLASS()
class HYPERION_API AShipWheel : public AShipboardChangeableObject
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;

};
