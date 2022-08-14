#include "HyperionCharacter.h"
#include "Net/UnrealNetwork.h"
#include "HyperionProjectile.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"
#include "ChangeableObject.h"


AHyperionCharacter::AHyperionCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	TurnRateGamepad = 45.f;
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	UPlayerMovement = GetCharacterMovement();
	CharacterCollision = GetCapsuleComponent();
	CharacterCollision->SetCollisionProfileName("Character");
}

void AHyperionCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AHyperionCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FirstPersonCameraComponent->FieldOfView = FMath::FInterpTo(FirstPersonCameraComponent->FieldOfView, FoV,
	                                                           DeltaSeconds, 8);
}


void AHyperionCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AHyperionCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AHyperionCharacter::StopRuning);

	/*CharacterCollision->OnComponentBeginOverlap.AddDynamic(this, &AHyperionCharacter::OnOverlapBegin);
	CharacterCollision->OnComponentEndOverlap.AddDynamic(this, &AHyperionCharacter::OnOverlapEnd);*/

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AHyperionCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AHyperionCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AHyperionCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AHyperionCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AHyperionCharacter::Interact);
}


void AHyperionCharacter::MoveForward(float Value)
{
	if (bIsControlling)
	{
		SetControlledYInput(Value);
	}
	else
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AHyperionCharacter::MoveRight(float Value)
{
	if (bIsControlling)
	{
		SetControlledXInput(Value);
	}
	else
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
	UPlayerMovement->MaxWalkSpeed = 1000;
	if (!HasAuthority())
	{
		FoV = 120;
	}
}

void AHyperionCharacter::StopRuning()
{
	UPlayerMovement->MaxWalkSpeed = 600;
	if (!HasAuthority())
	{
		FoV = 100;
	}
}

void AHyperionCharacter::Interact()
{
	InteractServer();
}

void AHyperionCharacter::InteractServer_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, "PRESSED F");
	if (bIsCanControl && ChangeableObject != nullptr && !bIsControlling)
	{
		if (!ChangeableObject->GetIsControlling())
		{
			ChangeableObject->SetIsControlling(true);
			ChangeableObject->SetHyperionPlayer(this);
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

void AHyperionCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHyperionCharacter, bIsCanControl);
	DOREPLIFETIME(AHyperionCharacter, ChangeableObject);
	DOREPLIFETIME(AHyperionCharacter, bIsControlling);
}


/*void AHyperionCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
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

void AHyperionCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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
}*/

void AHyperionCharacter::SetIsCanControl_Implementation(bool val)
{
	bIsCanControl = val;
}

void AHyperionCharacter::SetChangeableObject_Implementation(AChangeableObject* object)
{
	ChangeableObject = object;
}

void AHyperionCharacter::SetIsControlling_Implementation(bool val)
{
	bIsControlling = val;
}

void AHyperionCharacter::SetControlledXInput_Implementation(float X)
{
	ChangeableObject->SetInputRightValue(X);
}

void AHyperionCharacter::SetControlledYInput_Implementation(float Y)
{
	ChangeableObject->SetInputForwardValue(Y);
}
