// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject.h"

// Sets default values
AInteractiveObject::AInteractiveObject()
{
	PrimaryActorTick.bCanEverTick = true;
	InteractiveObjectTrigger = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	InteractiveObjectTrigger->OnComponentBeginOverlap.AddDynamic( this, &AInteractiveObject::OnOverlapBegin);
	InteractiveObjectTrigger->OnComponentEndOverlap.AddDynamic( this, &AInteractiveObject::OnOverlapEnd);
	InteractiveObjectTrigger->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void AInteractiveObject::BeginPlay()
{
	Super::BeginPlay();
}
// Called to bind functionality to input
void AInteractiveObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void  AInteractiveObject::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	}
}

void AInteractiveObject::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Overlap End"));
	}
}


