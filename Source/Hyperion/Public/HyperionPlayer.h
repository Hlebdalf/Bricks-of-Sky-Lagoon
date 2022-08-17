// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChangeableObject.h"
#include "Cannon.h"
#include "ASkyShip.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "HyperionPlayer.generated.h"


UCLASS()
class HYPERION_API AHyperionPlayer : public APawn
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* UHyperionPlayerCollision;
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* UHyperionPlayerTrigger;
	UPROPERTY()
	UCameraComponent* UHyperionPlayerCamera;
	
	UPROPERTY(Replicated, VisibleAnywhere, Category="PlayerMovement")
	float ForceMP = 100000.f * 3.3f;
	UPROPERTY()
	float XInput = 0.f;
	UPROPERTY()
	float YInput = 0.f;
	UPROPERTY()
	FVector PlayerRightVector;
	UPROPERTY()
	FVector PlayerForwardVector;
	UPROPERTY()
	bool bIsControlled = false;
	UPROPERTY()
	bool bIsOwningSkyShip = false;

	UPROPERTY()
	FVector NowOwnedShipLocation = FVector(0, 0, 0);
	UPROPERTY()
	FVector PreOwnedShipLocation = FVector(0, 0, 0);
	
	
	
	UPROPERTY(Replicated)
	FVector ForwardViewportVector;
	UPROPERTY(Replicated)
	FVector RightViewportVector;
	UPROPERTY(Replicated)
	FVector HyperionPlayerLocation;
	UPROPERTY(Replicated)
	bool bIsFalling = false;
	UPROPERTY(Replicated)
	bool bIsCanControl = false;
	UPROPERTY(Replicated)
	bool bIsControlling = false;
	UPROPERTY(Replicated)
	AChangeableObject* ChangeableObject;
	UPROPERTY()
	ASkyShip* OwnedSkyShip;
	
	UFUNCTION(Server, Reliable)
	void InteractServer();
	UFUNCTION(Server, Reliable)
	void SetIsCanControl(bool val);
	UFUNCTION(Server, Unreliable)
	void SetControlledXInput(float X);
	UFUNCTION(Server, Unreliable)
	void SetControlledYInput(float Y);
	UFUNCTION(Server, Unreliable)
	void SetIsFalling(bool how);
	UFUNCTION(Server, Unreliable)
	void SetIsControlling(bool val);
	UFUNCTION(Server, Reliable)
	void SetChangeableObject(AChangeableObject* object);
	UFUNCTION(Server, Reliable)
	void SpacePressed();
	
	UFUNCTION(Server, Unreliable)
	void SetXInput(float X);
	UFUNCTION(Server, Unreliable)
	void SetYInput(float Y);
	UFUNCTION(Server, Unreliable)
	void SetHyperionPlayerLocation(FVector dir);

	void Run();
	void StopRunning();

public:
	AHyperionPlayer();

protected:
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	void MoveForward(float Val);
	void MoveRight(float Val);
	void Jump();
	void Interact();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
					  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnTriggered(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);
	
};


