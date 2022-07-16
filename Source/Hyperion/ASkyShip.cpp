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

	BackArrow->SetRelativeLocation(FVector(-1500, 0, 0));
	ForwardArrow->SetRelativeLocation(FVector(1500, 0, 0));
	LeftArrow->SetRelativeLocation(FVector(0, 800, 0));
	RightArrow->SetRelativeLocation(FVector(0, -800, 0));

	/*AWheel = CreateDefaultSubobject<UChildActorComponent>(TEXT("Wheel"));
	AWheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);*/
	
	
	/*AWheel ->SetChildActorClass([AChangeableObject]::StaticClass());
	AWheel->ChildActorClass = 
	AWheel->CreateChildActor();*/

	const ConstructorHelpers::FObjectFinder<UStaticMesh> CorpusMesh(TEXT("/Game/Models/Ship_Mesh"));
	if (CorpusMesh.Succeeded())
	{
		SkyShipCorpus->SetStaticMesh(CorpusMesh.Object);
		SkyShipCorpus->SetSimulatePhysics(true);
		SkyShipCorpus->SetAngularDamping(AngDamping);
		SkyShipCorpus->SetLinearDamping(LinDamping);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CORPUS MESH NOT FOUND!"));
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
	SkyShipCorpus->AddForceAtLocationLocal(
		FVector(0, 0, UpForceMP * (SkyLevel - ForwardArrow->GetComponentLocation().Z)),
		ForwardArrow->GetRelativeLocation());
	SkyShipCorpus->AddForceAtLocationLocal(FVector(0, 0, UpForceMP * (SkyLevel - BackArrow->GetComponentLocation().Z)),
	                                       BackArrow->GetRelativeLocation());
	SkyShipCorpus->AddForceAtLocationLocal(FVector(0, 0, UpForceMP * (SkyLevel - LeftArrow->GetComponentLocation().Z)),
	                                       LeftArrow->GetRelativeLocation());
	SkyShipCorpus->AddForceAtLocationLocal(FVector(0, 0, UpForceMP * (SkyLevel - RightArrow->GetComponentLocation().Z)),
	                                       RightArrow->GetRelativeLocation());
}
