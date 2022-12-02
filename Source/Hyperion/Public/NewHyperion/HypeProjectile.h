// by Hlebdalf

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "HypeSkyShip.h"
#include "HypeBrickImporter.h"
#include "HypeProjectile.generated.h"

UCLASS()
class HYPERION_API AHypeProjectile : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* ProjectileCollision;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileMesh;
	
public:	
	AHypeProjectile();

protected:
	virtual void BeginPlay() override;
	void SetupCollision();
	void SetupMesh();

public:	
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void AddProjectileImpulse(FVector imuplse);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
