// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeableObject.h"

AChangeableObject::AChangeableObject()
{
	ChangeableObjectCamera = CreateDefaultSubobject<UCameraComponent>("ChangeableCamera");
	ChangeableObjectCamera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AChangeableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateValue();
}


void AChangeableObject::UpdateValue()
{
	FVector2D inputVector = InputDirection * GetWorld()->DeltaTimeSeconds * DirectionMP;
	if (DirectionThresholdFloor.X < Value.X + inputVector.X &&
		Value.X + inputVector.X < DirectionThresholdRoof.X &&
		DirectionThresholdFloor.Y < Value.Y + inputVector.Y
		&& Value.Y + inputVector.Y < DirectionThresholdRoof.Y)
	{
		Value += inputVector;
	}
}
