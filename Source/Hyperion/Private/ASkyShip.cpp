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
	
	SkyShipCorpus->SetAngularDamping(AngDamping);
	SkyShipCorpus->SetLinearDamping(LinDamping);
}

void ASkyShip::BeginPlay()
{
	Super::BeginPlay();
	EnablePhysicsOnServer();
}

void ASkyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!HasAuthority())
	{
		InterToTransform();
	}
	ASkyShip::UpdatePhysics();
}

void ASkyShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASkyShip::UpdatePhysics()
{
	if (HasAuthority())
	{
		SkyShipCorpus->AddForceAtLocationLocal(
			FVector(0, 0, UpForceMP * (TargetSkyLevel - ForwardArrow->GetComponentLocation().Z)),
			ForwardArrow->GetRelativeLocation());
		SkyShipCorpus->AddForceAtLocationLocal(
			FVector(0, 0, UpForceMP * (TargetSkyLevel - BackArrow->GetComponentLocation().Z)),
			BackArrow->GetRelativeLocation());
		SkyShipCorpus->AddForceAtLocationLocal(
			FVector(0, 0, UpForceMP * (TargetSkyLevel - LeftArrow->GetComponentLocation().Z)),
			LeftArrow->GetRelativeLocation());
		SkyShipCorpus->AddForceAtLocationLocal(
			FVector(0, 0, UpForceMP * (TargetSkyLevel - RightArrow->GetComponentLocation().Z)),
			RightArrow->GetRelativeLocation());
		SkyShipCorpus->AddTorqueInRadians(FVector(0, 0, SkyShipTorque));
		SkyShipCorpus->AddForce(GetActorForwardVector() * SkyShipSpeedMP);
		NowTransform = GetActorTransform();
	}
}

void ASkyShip::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASkyShip, NowTransform);
}

void ASkyShip::SetSkyShipTorque_Implementation(float Value)
{
	SkyShipTorque = Value;
}

void ASkyShip::SetSkyShipSpeedMP_Implementation(float Value)
{
	SkyShipSpeedMP = Value;
}

void ASkyShip::SetTagetSkyLevel_Implementation(float Value)
{
	TargetSkyLevel = StartSkyLevel + Value;
	
}

void ASkyShip::EnablePhysicsOnServer_Implementation()
{
	SkyShipCorpus->SetSimulatePhysics(true);
}

void ASkyShip::InterToTransform()
{	
	FQuat lol = FMath::QInterpTo(GetActorRotation().Quaternion(), NowTransform.GetRotation(), GetWorld()->DeltaTimeSeconds,12);
	FVector kek = FMath::VInterpTo(GetActorLocation(), NowTransform.GetLocation(), GetWorld()->DeltaTimeSeconds, 12);
	FTransform cheburek = FTransform(lol, kek, FVector(1,1,1));
	SetActorTransform(cheburek);
}
