#include "HyperionCharacter.h"
#include "HyperionProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"
// AHyperionCharacter

AHyperionCharacter::AHyperionCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	TurnRateGamepad = 45.f;
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	UPlayerMovement = GetCharacterMovement();
	
}

void AHyperionCharacter::BeginPlay()
{
	Super::BeginPlay();
	FoV = 120;
}

void AHyperionCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FirstPersonCameraComponent -> FieldOfView = FMath::FInterpTo(FirstPersonCameraComponent->FieldOfView, FoV, DeltaSeconds, 8);
}



void AHyperionCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{

	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AHyperionCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AHyperionCharacter::StopRuning);


	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AHyperionCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AHyperionCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AHyperionCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AHyperionCharacter::LookUpAtRate);
}


void AHyperionCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AHyperionCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AHyperionCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AHyperionCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AHyperionCharacter::Run()
{
	FoV = 120;
	UPlayerMovement -> MaxWalkSpeed = 1200;
}
void AHyperionCharacter::StopRuning()
{
	FoV = 100;
	UPlayerMovement -> MaxWalkSpeed = 600;
}
