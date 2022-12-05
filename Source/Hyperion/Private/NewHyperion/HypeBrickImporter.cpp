// by Hlebdalf


#include "NewHyperion/HypeBrickImporter.h"

AHypeBrickImporter::AHypeBrickImporter()
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);

}

void AHypeBrickImporter::BeginPlay()
{
	Super::BeginPlay();
}

void AHypeBrickImporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

