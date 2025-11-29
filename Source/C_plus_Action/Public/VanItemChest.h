// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VanGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "VanGameplayInterface.h"
#include "VanItemChest.generated.h"


class UStaticMeshComponent;
UCLASS()
class C_PLUS_ACTION_API AVanItemChest : public AActor, public IVanGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVanItemChest();
	void Interact_Implementation(APawn* InstigatorPawn);
	
	UPROPERTY(EditAnywhere)
	float TargetPitch;
protected:
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
