
#include "ASkyShip.h"

ASkyShip::ASkyShip()
{
	PrimaryActorTick.bCanEverTick = true;
	SkyShipCorpus = CreateDefaultSubobject<UStaticMeshComponent>("SkyShipCorpus");
	RootComponent = SkyShipCorpus;

	ForwardArrow = CreateDefaultSubobject<UArrowComponent>("ForwardArrow");
	BackArrow = CreateDefaultSubobject<UArrowComponent>("BackArrow");
	RightArrow = CreateDefaultSubobject<UArrowComponent>("RightArrow");
	LeftArrow = CreateDefaultSubobject<UArrowComponent>("LeftArrow");

	ForwardArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BackArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	RightArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	LeftArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	const ConstructorHelpers::FObjectFinder<UStaticMesh> CorpusMesh(TEXT("/Game/Models/Ship_Mesh"));
	if (CorpusMesh.Succeeded())
	{
		SkyShipCorpus -> SetStaticMesh(CorpusMesh.Object);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, "NoneMEsh");
	}
}

void ASkyShip::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ASkyShip::UpdatePhysics();

}

void ASkyShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASkyShip::UpdatePhysics()
{
	//SkyShipCorpus->AddForceAtLocationLocal(FVector(0,0,UpForceMP),ForwardArrow->GetRelativeLocation());
}

