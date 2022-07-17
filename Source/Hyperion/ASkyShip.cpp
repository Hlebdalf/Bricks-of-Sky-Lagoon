#include "ASkyShip.h"

#include "Net/UnrealNetwork.h"


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
	float delta = GetWorld()->DeltaTimeSeconds;
	SkyShipCorpus->AddForceAtLocationLocal(FVector(0, 0, UpForceMP * (TargetSkyLevel  - ForwardArrow->GetComponentLocation().Z)* delta),
							ForwardArrow->GetRelativeLocation());
	SkyShipCorpus->AddForceAtLocationLocal(FVector(0, 0, UpForceMP * (TargetSkyLevel  - BackArrow->GetComponentLocation().Z)* delta),
	                                       BackArrow->GetRelativeLocation());
	SkyShipCorpus->AddForceAtLocationLocal(FVector(0, 0, UpForceMP * (TargetSkyLevel - LeftArrow->GetComponentLocation().Z)* delta),
	                                       LeftArrow->GetRelativeLocation());
	SkyShipCorpus->AddForceAtLocationLocal(FVector(0, 0, UpForceMP * (TargetSkyLevel - RightArrow->GetComponentLocation().Z)* delta),
	                                       RightArrow->GetRelativeLocation());
	SkyShipCorpus->AddTorqueInRadians(FVector(0,0,SkyShipTorque* delta));
	SkyShipCorpus->AddForce(GetActorForwardVector()*SkyShipSpeedMP);
}

void ASkyShip::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASkyShip, SkyShipTorque);
	DOREPLIFETIME(ASkyShip, SkyShipSpeedMP);
	DOREPLIFETIME(ASkyShip, TargetSkyLevel);
}

void ASkyShip::SetSkyShipTorque_Implementation(float Value)
{
	SkyShipTorque = Value;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::SanitizeFloat(Value));
}
void ASkyShip::SetSkyShipSpeedMP_Implementation(float Value)
{
	SkyShipSpeedMP = Value;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::SanitizeFloat(Value));
}

void ASkyShip::SetTagetSkyLevel_Implementation(float Value)
{
	TargetSkyLevel = StartSkyLevel + Value;
}
