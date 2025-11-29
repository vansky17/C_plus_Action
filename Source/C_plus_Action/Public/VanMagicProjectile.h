#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "VanMagicProjectile.generated.h"

// Forward declarations
class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class C_PLUS_ACTION_API AVanMagicProjectile : public AActor
{
	GENERATED_BODY()

public:
	AVanMagicProjectile();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* EffectComp;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComp,
						 AActor* OtherActor,
						 UPrimitiveComponent* OtherComp,
						 FVector NormalImpulse,
						 const FHitResult& Hit);
};
