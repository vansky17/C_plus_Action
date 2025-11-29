// Fill out your copyright notice in the Description page of Project Settings.


#include "VanCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AVanCharacter::AVanCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp -> SetupAttachment(RootComponent);
	SpringArmComp -> bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject <UCameraComponent >("CameraComp");
	CameraComp -> SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;
	
	
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = true;
	
}

// Called when the game starts or when spawned
void AVanCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVanCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(), Value);
}
void AVanCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	FVector RighVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RighVector, Value);
}
void AVanCharacter::LookUp(float Value)
{
	float Sensitivity = 0.2f; // tune between 0.1 and 1.0
	AddControllerPitchInput(Value * Sensitivity);
}
// Called every frame
void AVanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVanCharacter::PrimaryAttack()
{
	if (!ProjectileClass) return;

	// ----- AIMING DIRECTION -----
	// Use camera forward vector to determine the direction of fire
	FVector ShotDirection = CameraComp->GetForwardVector();
	FRotator ShotRotation = ShotDirection.Rotation();

	// ----- SPAWN LOCATION -----
	// Spawn from the hand socket instead of camera
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	// Push it slightly forward so it doesn't intersect player capsule
	FVector SpawnLocation = HandLocation + ShotDirection * 20.f;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// ---- SPAWN ----
	GetWorld()->SpawnActor<AActor>(
		ProjectileClass,
		SpawnLocation,
		ShotRotation,
		Params
	);
}


// Called to bind functionality to input
void AVanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent -> BindAxis("MoveForward", this,&AVanCharacter::MoveForward);
	PlayerInputComponent -> BindAxis("Turn", this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVanCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AVanCharacter::LookUp);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent ->BindAction("PrimaryAttack", IE_Pressed, this, &AVanCharacter::PrimaryAttack);
}

