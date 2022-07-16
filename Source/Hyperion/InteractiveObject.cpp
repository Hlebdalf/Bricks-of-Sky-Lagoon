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
	InteractiveObjectTrigger->SetRelativeLocation(FVector(0,0,0));
	InteractiveObjectTrigger->SetCollisionProfileName(TEXT("Trigger"));
	InteractiveObjectTrigger->OnComponentBeginOverlap.AddDynamic( this, &AInteractiveObject::OnOverlapBegin);
	InteractiveObjectTrigger->OnComponentEndOverlap.AddDynamic( this, &AInteractiveObject::OnOverlapEnd);
}

void AInteractiveObject::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractiveObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent -> BindAction("Interact", IE_Pressed,this, &AInteractiveObject::PressedFButton);
}

void AInteractiveObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AInteractiveObject, HyperionCharacter);
}

void AInteractiveObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor) && OtherComp  && !GetIsControlling()) 
	{
		HyperionCharacter = Cast<ACharacter>(OtherActor);
		if (HyperionCharacter != nullptr)
		{
			
			//GEngine-> AddOnScreenDebugMessage(-1,5, FColor::Orange, GetIsControlling()?"ControllingInt":"NoncontrollingInt");
		}
	}
}

void AInteractiveObject::PressedFButton()
{
	GEngine-> AddOnScreenDebugMessage(-1,5, FColor::Black, "Pressed F On Object");
	if(GetPlayerState() != nullptr)
	{
		//GEngine-> AddOnScreenDebugMessage(-1,5, FColor::Black, GetPlayerState()->GetPlayerController()->GetName());
		SetIsControlling(false);
		PossessToCharacter();
	}
}

void  AInteractiveObject::SetHyperionCharacter_Implementation(ACharacter* object)
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
