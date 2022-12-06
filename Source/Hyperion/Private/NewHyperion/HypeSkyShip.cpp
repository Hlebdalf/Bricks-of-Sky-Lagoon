// by Hlebdalf


#include "NewHyperion/HypeSkyShip.h"

AHypeSkyShip::AHypeSkyShip()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHypeSkyShip::BeginPlay()
{
	Super::BeginPlay();	
}

void AHypeSkyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHypeSkyShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}