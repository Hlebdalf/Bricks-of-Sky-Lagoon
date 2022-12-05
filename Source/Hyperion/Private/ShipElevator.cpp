// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipElevator.h"

void AShipElevator::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SkyShip->SetTagetSkyLevel(Value.X* ValueMP.X);
}
