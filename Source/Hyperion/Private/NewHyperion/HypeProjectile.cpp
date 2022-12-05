// by Hlebdalf


#include "NewHyperion/HypeProjectile.h"

AHypeProjectile::AHypeProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	SetupCollision();
	RootComponent = ProjectileCollision;
	SetupMesh();
	ProjectileMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AHypeProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AHypeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AHypeProjectile::SetupCollision() 
{
	ProjectileCollision = CreateDefaultSubobject<UCapsuleComponent>("ProjectileCollision");
	ProjectileCollision->InitCapsuleSize(200, 200);
	ProjectileCollision->SetCollisionProfileName("Trigger");
	ProjectileCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ProjectileCollision->SetSimulatePhysics(true);
	ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &AHypeProjectile::OnBeginOverlap);
}


void AHypeProjectile::SetupMesh() 
{
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/PartsLib/PartsLib_3062PL"));
	ProjectileMesh->SetStaticMesh(MeshObj.Object);
	ProjectileMesh->SetWorldScale3D(FVector(0.6f, 0.6f, 0.6f));
	ProjectileMesh->SetRelativeRotation(FRotator(90, 0, 0));
	ProjectileMesh->SetCollisionProfileName("NoCollision");
}

void AHypeProjectile::AddProjectileImpulse(FVector impulse)
{
	ProjectileCollision->AddImpulse(impulse);
}

void AHypeProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHypeBrickImporter* SkyShip = Cast<AHypeBrickImporter>(OtherActor);
	if (SkyShip != nullptr) 
	{
		TArray<UPrimitiveComponent*> CollectedComponents;
		ProjectileCollision->GetOverlappingComponents(CollectedComponents);
		SkyShip->DamageShip(GetActorLocation(), CollectedComponents);
		int len = CollectedComponents.Num();
		if (len > 10) Destroy();
		//Destroy();
	}
}