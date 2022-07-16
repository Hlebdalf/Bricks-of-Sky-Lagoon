// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Net/UnrealNetwork.h"
#include "CoreMinimal.h"
#include "ChangableObject.h"
#include "GameFramework/Character.h"
#include "HyperionCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class AHyperionCharacter : public ACharacter
{	
	GENERATED_BODY()
	UPROPERTY()
	UCharacterMovementComponent* UPlayerMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
	UPROPERTY()
	UCapsuleComponent* CharacterCollision;
	UPROPERTY(Replicated)
	AChangableObject* ChangableObject;
	float FoV;
	UPROPERTY()
	bool bIsControlling = false;
	UPROPERTY(Replicated)
	bool bIsCanControl = false;
	
	UFUNCTION(Server, Reliable)
	void InteractServer();
	UFUNCTION(Server, Reliable)
	void SetIsCanControl(bool val);
	UFUNCTION(Server, Reliable)
	void SetChangableObject(AChangableObject* object);
	UFUNCTION(NetMulticast, Reliable)
	void StopMovement();

public:
	AHyperionCharacter();

protected:
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaSeconds) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	
	float TurnRateGamepad;

protected:
	
	void MoveForward(float Val);
	void Run();
	void StopRuning();
	void MoveRight(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);	
	void Interact();
	
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;


public:
	UFUNCTION()	
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
					  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
};

