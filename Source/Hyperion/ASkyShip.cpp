// Fill out your copyright notice in the Description page of Project Settings.


#include "ASkyShip.h"

// Sets default values
ASkyShip::ASkyShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkyShipCorpus = CreateDefaultSubobject<UStaticMeshComponent>("SkyShipCorpus");
	RootComponent = SkyShipCorpus;

}

// Called when the game starts or when spawned
void ASkyShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkyShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

