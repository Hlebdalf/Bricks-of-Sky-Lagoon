// Fill out your copyright notice in the Description page of Project Settings.


#include "HyperionPlayer.h"

#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"

AHyperionPlayer::AHyperionPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	UHyperionPlayerCamera = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	UHyperionPlayerCollision = CreateDefaultSubobject<UCapsuleComponent>("PlayerCollision");
	UHyperionPlayerTrigger = CreateDefaultSubobject<UCapsuleComponent>("Trigger");

	UHyperionPlayerCollision->InitCapsuleSize(55.f, 55.f);
	UHyperionPlayerTrigger->InitCapsuleSize(80.f, 80.f);
	UHyperionPlayerCamera->SetupAttachment(UHyperionPlayerCollision);
	UHyperionPlayerTrigger->SetupAttachment(UHyperionPlayerCollision);
	UHyperionPlayerCamera->SetRelativeLocation(FVector(-39.56f, 1.75f, 100.f));
	UHyperionPlayerCamera->bUsePawnControlRotation = true;
	UHyperionPlayerCamera->FieldOfView = 110;

	this->NetUpdateFrequency = 60;
	this->MinNetUpdateFrequency = 30;

	bUseControllerRotationYaw = true;
	RootComponent = UHyperionPlayerCollision;
	UHyperionPlayerCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	UHyperionPlayerCollision->SetSimulatePhysics(true);
	UHyperionPlayerCollision->SetCollisionProfileName("Pawn");
	UHyperionPlayerCollision->BodyInstance.bLockXRotation = true;
	UHyperionPlayerCollision->BodyInstance.bLockYRotation = true;
	UHyperionPlayerCollision->BodyInstance.AngularDamping = 1;
	UHyperionPlayerCollision->BodyInstance.LinearDamping = 1;
	UHyperionPlayerCollision->SetNotifyRigidBodyCollision(true);
}

void AHyperionPlayer::BeginPlay()
{
	Super::BeginPlay();
	HyperionPlayerLocation = GetActorLocation();
	bIsControlled = this->IsPawnControlled();
}

void AHyperionPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!HasAuthority())
	{
		if (bIsControlling)
		{
			SetControlledYInput(YInput);
			SetControlledXInput(XInput);
		}
		else
		{
			PlayerForwardVector = ForwardViewportVector * ForceMP * DeltaTime * YInput;
			PlayerRightVector = RightViewportVector * ForceMP * DeltaTime * XInput;
			if (!bIsFalling)
			{
				UHyperionPlayerCollision->AddForce(PlayerForwardVector + PlayerRightVector);
			}
			else
			{
				UHyperionPlayerCollision->AddForce((PlayerForwardVector + PlayerRightVector) / 4);
			}
		}
		SetHyperionPlayerLocation(GetActorLocation());
	}
	if (!bIsControlled)
	{
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), HyperionPlayerLocation, DeltaTime, 12));
	}
}

void AHyperionPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AHyperionPlayer::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AHyperionPlayer::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHyperionPlayer::Jump);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AHyperionPlayer::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AHyperionPlayer::StopRunning);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AHyperionPlayer::Interact);

	UHyperionPlayerCollision->OnComponentBeginOverlap.AddDynamic(this, &AHyperionPlayer::OnOverlapBegin);
	UHyperionPlayerCollision->OnComponentEndOverlap.AddDynamic(this, &AHyperionPlayer::OnOverlapEnd);

	UHyperionPlayerTrigger->OnComponentBeginOverlap.AddDynamic(this, &AHyperionPlayer::OnTriggered);
}


void AHyperionPlayer::MoveForward(float Val)
{
	YInput = Val;
	if (!HasAuthority())
	{
		ForwardViewportVector = FVector::VectorPlaneProject(
			UHyperionPlayerCamera->GetForwardVector(), FVector(0, 0, 1));
	}
}

void AHyperionPlayer::MoveRight(float Val)
{
	XInput = Val;
	if (!HasAuthority())
	{
		RightViewportVector = FVector::VectorPlaneProject(
			UHyperionPlayerCamera->GetRightVector(), FVector(0, 0, 1));
	}
}

void AHyperionPlayer::Jump()
{
	if (!bIsFalling)
	{
		bIsFalling = true;
		UHyperionPlayerCollision->AddImpulse(FVector(0, 0, 200000));
	}
}

void AHyperionPlayer::Run()
{
	ForceMP *= 1.8f;
}

void AHyperionPlayer::StopRunning()
{
	ForceMP /= 1.8f;
}

void AHyperionPlayer::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                                     class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                     const FHitResult& SweepResult)
{
	if (OtherActor && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, "YouCanControl on F ");
		ChangeableObject = Cast<AChangeableObject>(OtherActor);
		if (ChangeableObject != nullptr)
		{
			SetChangeableObject(ChangeableObject);
			SetIsCanControl(true);
		}
	}
}

void AHyperionPlayer::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherComp)
	{
		ChangeableObject = Cast<AChangeableObject>(OtherActor);
		if (ChangeableObject != nullptr)
		{
			SetIsCanControl(false);
		}
	}
}

void AHyperionPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHyperionPlayer, bIsCanControl);
	DOREPLIFETIME(AHyperionPlayer, ChangeableObject);
	DOREPLIFETIME(AHyperionPlayer, bIsControlling);
	DOREPLIFETIME(AHyperionPlayer, bIsFalling);
	DOREPLIFETIME(AHyperionPlayer, HyperionPlayerLocation);
}

void AHyperionPlayer::SetIsCanControl_Implementation(bool val)
{
	bIsCanControl = val;
}

void AHyperionPlayer::SetChangeableObject_Implementation(AChangeableObject* object)
{
	ChangeableObject = object;
}

void AHyperionPlayer::SetIsControlling_Implementation(bool val)
{
	bIsControlling = val;
}

void AHyperionPlayer::SetControlledXInput_Implementation(float X)
{
	ChangeableObject->SetInputRightValue(X);
}

void AHyperionPlayer::SetControlledYInput_Implementation(float Y)
{
	ChangeableObject->SetInputForwardValue(Y);
}

void AHyperionPlayer::Interact()
{
	InteractServer();
}

void AHyperionPlayer::InteractServer_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, "PRESSED F");
	if (bIsCanControl && ChangeableObject != nullptr && !bIsControlling)
	{
		if (!ChangeableObject->GetIsControlling())
		{
			ChangeableObject->SetIsControlling(true);
			SetIsControlling(true);
			bIsControlling = true;
		}
	}
	else if (ChangeableObject != nullptr && bIsControlling)
	{
		SetControlledXInput_Implementation(0);
		SetControlledYInput_Implementation(0);
		SetIsControlling(false);
		ChangeableObject->SetIsControlling(false);
	}
}

void AHyperionPlayer::SetIsFalling_Implementation(bool how)
{
	bIsFalling = how;
}

void AHyperionPlayer::SetXInput_Implementation(float X)
{
	XInput = X;
}

void AHyperionPlayer::SetYInput_Implementation(float Y)
{
	YInput = Y;
}

void AHyperionPlayer::OnTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	bIsFalling = false;
}

void AHyperionPlayer::SetHyperionPlayerLocation_Implementation(FVector dir)
{
	HyperionPlayerLocation = dir;
}
