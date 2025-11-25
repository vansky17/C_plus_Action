// Fill out your copyright notice in the Description page of Project Settings.


#include "VanCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AVanCharacter::AVanCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp -> SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject <UCameraComponent >("CameraComp");
	CameraComp -> SetupAttachment(SpringArmComp);
	
	//SpringArmComp->bUsePawnControlRotation = true;
	//CameraComp->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AVanCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVanCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}
void AVanCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}
// Called every frame
void AVanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent -> BindAxis("MoveForward", this,&AVanCharacter::MoveForward);
	PlayerInputComponent -> BindAxis("Turn", this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVanCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

