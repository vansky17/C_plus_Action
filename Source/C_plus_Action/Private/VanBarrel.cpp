// Fill out your copyright notice in the Description page of Project Settings.


#include "VanBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "VanMagicProjectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AVanBarrel::AVanBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
	RootComponent = BarrelMesh;
	BarrelMesh->SetSimulatePhysics(true);
	BarrelMesh->SetNotifyRigidBodyCollision(true);  // VERY IMPORTANT FOR HIT EVENTS
	BarrelMesh->SetCollisionProfileName("PhysicsActor");

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(BarrelMesh);
	RadialForceComp->Radius = 800.0f;
	RadialForceComp->ImpulseStrength = 2000.0f;
	RadialForceComp->bImpulseVelChange = true;
}

// Called when the game starts or when spawned
void AVanBarrel::BeginPlay()
{
	Super::BeginPlay();
	
	BarrelMesh->OnComponentHit.AddDynamic(this, &AVanBarrel::OnHit);
}

void AVanBarrel::OnHit(UPrimitiveComponent* HitComp,
					   AActor* OtherActor,
					   UPrimitiveComponent* OtherComp,
					   FVector NormalImpulse,
					   const FHitResult& Hit)
{
	if (!OtherActor || OtherActor == this)
		return;

	// Only react to the projectile
	if (!OtherActor->IsA(AVanMagicProjectile::StaticClass()))
		return;

	UE_LOG(LogTemp, Warning, TEXT("Barrel HIT by projectile!"));

	RadialForceComp->FireImpulse();
}

// Called every frame
void AVanBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

