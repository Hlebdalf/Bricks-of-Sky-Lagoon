// by Hlebdalf


#include "NewHyperion/HypeProjectile.h"

AHypeProjectile::AHypeProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	SetupCollision();
	RootComponent = ProjectileCollision;
	SetupMesh();
	//ProjectileMesh->SetupAttachment(ProjectileCollision);
	ProjectileMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AHypeProjectile::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Hello world");
}

void AHypeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHypeProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	//UInstancedStaticMeshComponent* InstancedPart = (UInstancedStaticMeshComponent*)OtherComp;
	AHypeBrickImporter* SkyShip = Cast<AHypeBrickImporter>(OtherActor);
	//AHypeBrickImporter* SkyShip = (AHypeBrickImporter*)(OtherActor);
	//AHypeSkyShip* SkyShip = Cast<AHypeSkyShip>(OtherActor);
	//if (InstancedPart != nullptr) {
	//	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, OtherComp->GetName() + " " + OtherComp->GetName());// + " " + OtherComp-GetName()
	//}
	if (SkyShip != nullptr) {
		/*if (InstancedPart != nullptr) {
			SkyShip->DamageShip(GetActorLocation(), InstancedPart);
		}*/
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, OtherComp->GetName() + " " + OtherActor->GetName());
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, SkyShip->GetClass()->GetName());
		SkyShip->DamageShip(GetActorLocation(), OtherComp);
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, InstancedPart->GetClass());
}



void AHypeProjectile::SetupCollision() 
{
	ProjectileCollision = CreateDefaultSubobject<UCapsuleComponent>("ProjectileCollision");
	ProjectileCollision->InitCapsuleSize(54, 54);
	ProjectileCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ProjectileCollision->SetCollisionProfileName("BlockAll");
	ProjectileCollision->SetNotifyRigidBodyCollision(true);
	ProjectileCollision->SetSimulatePhysics(true);
	ProjectileCollision->OnComponentHit.AddDynamic(this, &AHypeProjectile::OnHit);
}


void AHypeProjectile::SetupMesh() 
{
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/PartsLib/PartsLib_3062PL"));
	ProjectileMesh->SetStaticMesh(MeshObj.Object);
	ProjectileMesh->SetWorldScale3D(FVector(0.6f, 0.6f, 0.6f));
	ProjectileMesh->SetRelativeRotation(FRotator(90, 0, 0));
}

void AHypeProjectile::AddProjectileImpulse(FVector impulse)
{
	ProjectileCollision->AddImpulse(impulse);
}