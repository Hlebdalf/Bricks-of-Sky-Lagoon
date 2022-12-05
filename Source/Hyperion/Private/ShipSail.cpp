// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipSail.h"

void AShipSail::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, Value.ToString());
	SkyShip->SetSkyShipSpeedMP(Value.X * ValueMP.X);
}
