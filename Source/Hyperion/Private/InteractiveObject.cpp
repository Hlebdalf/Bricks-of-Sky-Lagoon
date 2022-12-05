// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractiveObject.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"

AInteractiveObject::AInteractiveObject()
{
	PrimaryActorTick.bCanEverTick = true;
	UInteractiveMesh = CreateDefaultSubobject<UStaticMeshComponent>("DefaultInteractiveMesh");
	RootComponent = UInteractiveMesh;
	InteractiveObjectTrigger = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	InteractiveObjectTrigger->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	InteractiveObjectTrigger->SetRelativeLocation(FVector(0, 0, 0));
	InteractiveObjectTrigger->SetCollisionProfileName(TEXT("Trigger"));
}

void AInteractiveObject::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractiveObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AInteractiveObject, HyperionPlayer);
	DOREPLIFETIME(AInteractiveObject, InputDirection);
}


void AInteractiveObject::SetHyperionPlayer_Implementation(APawn* object)
{
	HyperionPlayer = object;
}

bool AInteractiveObject::GetIsControlling()
{
	return bIsControlling;
}

void AInteractiveObject::SetIsControlling_Implementation(bool how)
{
	bIsControlling = how;
}

void AInteractiveObject::SetInputForwardValue_Implementation(float Value)
{
	SetInputDirection(InputDirection.X, Value);
	//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan, FString::SanitizeFloat(Value));
}

void AInteractiveObject::SetInputRightValue_Implementation(float Value)
{
	SetInputDirection(Value, InputDirection.Y);
	//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Yellow, FString::SanitizeFloat(Value));
}

void AInteractiveObject::SetInputDirection_Implementation(float LeftRightValue, float ForwardBackValue)
{	
	if (bIsControlling) {
		InputDirection = FVector2D(LeftRightValue, ForwardBackValue);
	}
	else {
		InputDirection = FVector2D(0, 0);
	}
	
}
