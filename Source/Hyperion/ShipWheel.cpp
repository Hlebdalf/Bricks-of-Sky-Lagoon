// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipWheel.h"

AShipWheel::AShipWheel()
{
	//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Orange, "I AM EXIST!");
}

void AShipWheel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SkyShip->SetSkyShipTorque(Value.X * ValueMP.X);
}
