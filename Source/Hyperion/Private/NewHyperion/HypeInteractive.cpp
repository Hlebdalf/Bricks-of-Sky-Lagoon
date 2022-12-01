// by Hlebdalf


#include "NewHyperion/HypeInteractive.h"

// Sets default values
AHypeInteractive::AHypeInteractive()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHypeInteractive::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHypeInteractive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHypeInteractive::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

