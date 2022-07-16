// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipboardChangeableObject.h"

void AShipboardChangeableObject::BeginPlay()
{
	SkyShip = Cast<ASkyShip>(GetDefaultAttachComponent()->GetAttachParent()->GetAttachParent()->GetOwner());
}
