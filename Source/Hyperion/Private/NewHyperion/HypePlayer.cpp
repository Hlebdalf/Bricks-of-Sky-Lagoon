// by Hlebdalf


#include "NewHyperion/HypePlayer.h"

// Sets default values
AHypePlayer::AHypePlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHypePlayer::BeginPlay()
{
	Super::BeginPlay();

}

void AHypePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHypePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

