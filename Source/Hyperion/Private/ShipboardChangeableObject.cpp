// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipboardChangeableObject.h"

void AShipboardChangeableObject::BeginPlay()
{
	Super::BeginPlay();
	SkyShip = Cast<ASkyShip>(GetDefaultAttachComponent()->GetAttachParent()->GetAttachParent()->GetOwner());
}

void AShipboardChangeableObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
