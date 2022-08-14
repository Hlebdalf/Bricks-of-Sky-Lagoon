// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

ACannon::ACannon()
{
	UCannonMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cannon Mesh");
	//UCannonMesh->SetupAttachment(UInteractiveMesh);
	UCannonMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//UCannonMesh->AddLocalRotation(FRotator(0,90,0));
	
}

void ACannon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SetActorRelativeRotation(FRotator(0, Value.X * ValueMP.X, 0));
	UCannonMesh->SetRelativeRotation(FRotator(0, 270, -Value.Y * ValueMP.Y));
}

/*void ACannon::kuko_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Emerald,"Jumped!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
}*/

void ACannon::CannonShoot_Implementation() {
	Fire();
}