// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipWheel.h"


void AShipWheel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SkyShip->SetSkyShipTorque(Value.X * ValueMP.X);
	//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Purple, FString::SanitizeFloat(Value.X * ValueMP.X));
}
