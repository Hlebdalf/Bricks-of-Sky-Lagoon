// by Hlebdalf


#include "NewHyperion/HypeBrickImporter.h"

// Sets default values
AHypeBrickImporter::AHypeBrickImporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);

}

// Called when the game starts or when spawned
void AHypeBrickImporter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHypeBrickImporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

