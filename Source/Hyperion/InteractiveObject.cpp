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

void AInteractiveObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AInteractiveObject::SetInputForwardBackValue);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AInteractiveObject::SetInputLeftRightValue);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AInteractiveObject::PressedFButton);
}

void AInteractiveObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AInteractiveObject, HyperionCharacter);
}


void AInteractiveObject::PressedFButton()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, "Pressed F On Object");
	if (GetPlayerState() != nullptr)
	{
		SetIsControlling(false);
		PossessToCharacter();
	}
}

void AInteractiveObject::SetHyperionCharacter_Implementation(ACharacter* object)
{
	HyperionCharacter = object;
}

void AInteractiveObject::PossessToCharacter_Implementation()
{
	GetPlayerState()->GetPlayerController()->Possess(HyperionCharacter);
}


bool AInteractiveObject::GetIsControlling()
{
	return bIsControlling;
}

void AInteractiveObject::SetIsControlling_Implementation(bool how)
{
	bIsControlling = how;
}

void AInteractiveObject::SetInputForwardBackValue(float Value)
{
	SetInputDirection(InputDirection.X, Value);
}

void AInteractiveObject::SetInputLeftRightValue(float Value)
{
	SetInputDirection(Value,InputDirection.Y);
}

void AInteractiveObject::SetInputDirection_Implementation(float LeftRightValue, float ForwardBackValue)
{
	InputDirection = FVector2D(LeftRightValue,ForwardBackValue);
	//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Purple, InputDirection.ToString());
}

