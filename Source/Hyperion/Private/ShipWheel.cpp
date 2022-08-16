// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipWheel.h"

AShipWheel::AShipWheel() 
{
	UShipWheelMesh = CreateDefaultSubobject<UStaticMeshComponent>("WheelMesh");

}
void AShipWheel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SkyShip->SetSkyShipTorque(Value.X * ValueMP.X);
	//UShipWheelMesh->SetRelativeRotation(FRotator(0, 0, Value.X));
	UShipWheelMesh->SetRelativeRotation(FMath::RInterpTo(UShipWheelMesh->GetRelativeRotation(), FRotator(0, 0, Value.X), DeltaSeconds, 0.5f));
	//FMath::RInterpTo(UShipWheelMesh->GetRelativeRotation(), FRotator(0, 0, Value.X), DeltaSeconds, 2);
}



