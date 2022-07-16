// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASkyShip.h"
#include "ChangeableObject.h"
#include "ShipboardChangeableObject.generated.h"

/**
 * 
 */
UCLASS()
class HYPERION_API AShipboardChangeableObject : public AChangeableObject
{
	GENERATED_BODY()
	UPROPERTY()
	ASkyShip* SkyShip;

public:
	AShipboardChangeableObject();
};
