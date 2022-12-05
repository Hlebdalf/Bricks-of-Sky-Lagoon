// by Hlebdalf


#include "NewHyperion/HypeSkyShip.h"

// Sets default values
AHypeSkyShip::AHypeSkyShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHypeSkyShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHypeSkyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHypeSkyShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//void AHypeSkyShip::DamageShip(FVector loc) {
//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Ship damaged C++");
//}