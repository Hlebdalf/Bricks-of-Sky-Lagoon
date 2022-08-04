// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChangeableObject.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "HyperionPlayer.generated.h"

UCLASS()
class HYPERION_API AHyperionPlayer : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* UHyperionPlayerCollision;
	UPROPERTY()
	UCameraComponent* UHyperionPlayerCamera;
	
	UPROPERTY(Replicated, VisibleAnywhere, Category="PlayerMovement")
	float ForceMP = 10000000.f * 1.3f;
	UPROPERTY(Replicated)
	float XInput = 0.f;
	UPROPERTY(Replicated)
	float YInput = 0.f;
	UPROPERTY()
	FVector PlayerRightVector;
	UPROPERTY()
	FVector PlayerForwardVector;
	UPROPERTY()
	FVector ForwardViewportVector;
	UPROPERTY()
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
	
	UFUNCTION(Server, Reliable)
	void InteractServer();
	UFUNCTION(Server, Reliable)
	void JumpServer();
	UFUNCTION(Server, Reliable)
	void SetForceMP(bool isRunning);
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
	
	UFUNCTION(Server, Unreliable)
	void SetXInput(float X);
	UFUNCTION(Server, Unreliable)
	void SetYInput(float Y);
	UFUNCTION(Server, Unreliable)
	void SetRightViewportVector(FVector dir);
	UFUNCTION(Server, Unreliable)
	void SetForwardViewportVector(FVector dir);
		

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
	void OnHit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
						class UPrimitiveComponent* OtherComp, FVector NormalImpulse,
						const FHitResult& Hit);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
					  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/*UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
					  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);*/

};


