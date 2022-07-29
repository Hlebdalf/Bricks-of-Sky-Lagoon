// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
	UPROPERTY(VisibleAnywhere, Category="PlayerMovement")
	float ForceMP = 10000000 * 1.6f;
	UPROPERTY()
	float XInput = 1.f;
	UPROPERTY()
	float YInput = 1.f;
	UPROPERTY()
	bool bIsFalling = true;

	void Run();
	void StopRuning();

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
	UFUNCTION()
	void OnHit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
						class UPrimitiveComponent* OtherComp, FVector NormalImpulse,
						const FHitResult& Hit);

	/*UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
					  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);*/

};
