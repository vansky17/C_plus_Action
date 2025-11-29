#include "VanMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Critical for applying damage or interacting
#include "Kismet/GameplayStatics.h"


AVanMagicProjectile::AVanMagicProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    // ---- COLLISION COMPONENT ----
    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    RootComponent = SphereComp;

    SphereComp->InitSphereRadius(15.0f);
    SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SphereComp->SetCollisionObjectType(ECC_WorldDynamic);

    // Must block both static and dynamic for barrels
    SphereComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
    SphereComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
    SphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block);
    SphereComp->InitSphereRadius(15.f);

    SphereComp->SetNotifyRigidBodyCollision(true);
    SphereComp->SetGenerateOverlapEvents(false);  // We want hit, not overlap
    // IGNORE player
    SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

    // Bind hit event
    SphereComp->OnComponentHit.AddDynamic(this, &AVanMagicProjectile::OnProjectileHit);

    // ---- EFFECT COMPONENT ----
    EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComp"));
    EffectComp->SetupAttachment(SphereComp);

    // ---- MOVEMENT COMPONENT ----
    MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
    MovementComp->InitialSpeed = 1200.0f;
    MovementComp->MaxSpeed = 1200.0f;

    MovementComp->bRotationFollowsVelocity = true;
    MovementComp->bInitialVelocityInLocalSpace = true;
    MovementComp->bSweepCollision = true;
    MovementComp->ProjectileGravityScale = 0.0f;

    // CRITICAL — this makes the projectile collide properly!
    MovementComp->bSweepCollision = true;
    MovementComp->ProjectileGravityScale = 0.0f;  // No gravity (you can enable if needed)
}

void AVanMagicProjectile::BeginPlay()
{
    Super::BeginPlay();
}

void AVanMagicProjectile::OnProjectileHit(UPrimitiveComponent* HitComp,
                                          AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp,
                                          FVector NormalImpulse,
                                          const FHitResult& Hit)
{
    UE_LOG(LogTemp, Warning, TEXT("PROJECTILE HIT: %s"), *OtherActor->GetName());

    Destroy();
}
