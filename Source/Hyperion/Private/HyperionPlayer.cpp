// Fill out your copyright notice in the Description page of Project Settings.


#include "HyperionPlayer.h"

AHyperionPlayer::AHyperionPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	UHyperionPlayerCamera = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	UHyperionPlayerCollision = CreateDefaultSubobject<UCapsuleComponent>("PlayerCollision");

	UHyperionPlayerCollision->InitCapsuleSize(55.f, 55.f);
	UHyperionPlayerCamera->SetupAttachment(UHyperionPlayerCollision);
	UHyperionPlayerCamera->SetRelativeLocation(FVector(-39.56f, 1.75f, 100.f));
	UHyperionPlayerCamera->bUsePawnControlRotation = true;
	UHyperionPlayerCamera->FieldOfView = 110;

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

// Called when the game starts or when spawned
void AHyperionPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHyperionPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHyperionPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AHyperionPlayer::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AHyperionPlayer::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHyperionPlayer::Jump);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AHyperionPlayer::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AHyperionPlayer::StopRuning);

	UHyperionPlayerCollision->OnComponentHit.AddDynamic(this, &AHyperionPlayer::OnHit);
}


void AHyperionPlayer::MoveForward(float Val)
{
	YInput = FMath::Abs(Val);

	if (Val != 0)
	{
		const FVector PlayerForwardVector = FVector::VectorPlaneProject(UHyperionPlayerCamera->GetForwardVector(),FVector(0, 0, 1))/ (XInput + YInput);
		if (!bIsFalling)
		{
			UHyperionPlayerCollision->AddForce( PlayerForwardVector * ForceMP * Val * GetWorld()->DeltaTimeSeconds);
		}
		else
		{
			UHyperionPlayerCollision->AddForce( PlayerForwardVector * ForceMP * Val / 4 * GetWorld()->DeltaTimeSeconds);
		}
	}
}

void AHyperionPlayer::MoveRight(float Val)
{
	XInput = FMath::Abs(Val);

	if (Val != 0)
	{
		const FVector PlayerRightVector = FVector::VectorPlaneProject(UHyperionPlayerCamera->GetRightVector(),FVector(0, 0, 1))/ (XInput + YInput);
		if (!bIsFalling)
		{
			UHyperionPlayerCollision->AddForce(PlayerRightVector * ForceMP * Val * GetWorld()->DeltaTimeSeconds);
		}
		else
		{
			UHyperionPlayerCollision->AddForce(PlayerRightVector * ForceMP * Val / 4* GetWorld()->DeltaTimeSeconds);
		}
	}
}

void AHyperionPlayer::Jump()
{
	if (!bIsFalling)
	{
		bIsFalling = true;
		UHyperionPlayerCollision->AddImpulse(FVector(0, 0, 100000));
	}
}

void AHyperionPlayer::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            FVector NormalImpulse, const FHitResult& Hit)
{
	bIsFalling = false;
}

void AHyperionPlayer::Run()
{
	ForceMP *= 1.5f;
}

void AHyperionPlayer::StopRuning()
{
	ForceMP /= 1.5f;
}
