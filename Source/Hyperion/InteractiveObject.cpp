// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject.h"

// Sets default values
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
	//RootComponent = InteractiveObjectTrigger;
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

void AInteractiveObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AInteractiveObject::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}



