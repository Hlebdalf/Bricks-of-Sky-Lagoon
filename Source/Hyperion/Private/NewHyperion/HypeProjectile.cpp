// by Hlebdalf


#include "NewHyperion/HypeProjectile.h"

// Sets default values
AHypeProjectile::AHypeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHypeProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHypeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

