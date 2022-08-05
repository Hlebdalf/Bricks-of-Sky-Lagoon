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
	UHyperionPlayerTrigger ->InitCapsuleSize(80.f, 80.f);
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

	/*if (!HasAuthority())
	{
		UHyperionPlayerCollision->SetCollisionProfileName("NoCollision");
	}*/
	
}

void AHyperionPlayer::BeginPlay()
{
	Super::BeginPlay();
	HyperionPlayerLocation = GetActorLocation();
	//GetPlayerState()->GetPlayerController();
}

void AHyperionPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
		if (HasAuthority())
		{
			HyperionPlayerLocation = GetActorLocation();
			//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, HyperionPlayerLocation.ToString());
		}
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
	SetYInput(Val);
	YInput = Val;
	if (!HasAuthority())
	{
		SetForwardViewportVector(FVector::VectorPlaneProject(
			UHyperionPlayerCamera->GetForwardVector(), FVector(0, 0, 1)));
	}
}

void AHyperionPlayer::MoveRight(float Val)
{
	SetXInput(Val);
	XInput = Val;
	if (!HasAuthority())
	{
		SetRightViewportVector(FVector::VectorPlaneProject(
			UHyperionPlayerCamera->GetRightVector(), FVector(0, 0, 1)));
	}
}

void AHyperionPlayer::Jump()
{
	if (!bIsFalling)
	{
		SetIsFalling(true);
		UHyperionPlayerCollision->AddImpulse(FVector(0, 0, 200000));
		JumpServer();
	}
}

void AHyperionPlayer::JumpServer_Implementation()
{
	UHyperionPlayerCollision->AddImpulse(FVector(0, 0, 200000));
}

void AHyperionPlayer::Run()
{
	SetForceMP(true);
}

void AHyperionPlayer::StopRunning()
{
	SetForceMP(false);
}

void AHyperionPlayer::SetForceMP_Implementation(bool isRunning)
{
	if (isRunning)
	{
		ForceMP *= 1.8f;
	}
	else
	{
		ForceMP /= 1.8f;
	}
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
	/*DOREPLIFETIME(AHyperionPlayer, XInput);
	DOREPLIFETIME(AHyperionPlayer, YInput);*/
	DOREPLIFETIME(AHyperionPlayer, HyperionPlayerLocation);
	DOREPLIFETIME(AHyperionPlayer, ForceMP);
	DOREPLIFETIME(AHyperionPlayer, ForwardViewportVector);
	DOREPLIFETIME(AHyperionPlayer, RightViewportVector);
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
		SetIsControlling(false);
		ChangeableObject->SetIsControlling(false);
		SetControlledXInput_Implementation(0);
		SetControlledYInput_Implementation(0);
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


void AHyperionPlayer::SetForwardViewportVector_Implementation(FVector dir)
{
	ForwardViewportVector = dir;
}

void AHyperionPlayer::SetRightViewportVector_Implementation(FVector dir)
{
	RightViewportVector = dir;
}

void AHyperionPlayer::UpdateHyperionPlayerLocation()
{
	//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, HyperionPlayerLocation.ToString());
	SetActorLocation(FMath::VInterpTo(GetActorLocation(), HyperionPlayerLocation, GetWorld()->DeltaTimeSeconds, 30));
}

void AHyperionPlayer::OnTriggered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan, "Triggered!");
	SetIsFalling(false);
	bIsFalling = false;
}



