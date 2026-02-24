// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Rifle.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Spring Arm Setup
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetRelativeLocation(FVector(0.0f, 8.0f, 70.0f));
	SpringArm->SetRelativeRotation(FRotator(-40.f, 0.f, 0.f));

	//Camera Setup
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Pawn Camera"));
	Camera->SetupAttachment(SpringArm);

	//Possess Player.
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		Subsystem->AddMappingContext(characterMappingContext, 0);
	}

	//Maybe move to a seperate function.
	Weapon = GetWorld()->SpawnActor<ARifle>(RifleClass);

	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RifleSocket"));

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EIC->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForwardHandler);
	EIC->BindAction(StrafeAction, ETriggerEvent::Triggered, this, &APlayerCharacter::StrafeHandler);
	EIC->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LookUpHandler);
	EIC->BindAction(TurnAction, ETriggerEvent::Triggered, this, &APlayerCharacter::TurnHandler);
	EIC->BindAction(SprintAction, ETriggerEvent::Started, this, &APlayerCharacter::SprintHandler);
	EIC->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::SprintHandler);
	EIC->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EIC->BindAction(CrouchAction, ETriggerEvent::Started, this, &APlayerCharacter::CrouchHandler);
	EIC->BindAction(CrouchAction, ETriggerEvent::Completed, this, &APlayerCharacter::UnCrouchHandler);
}

void APlayerCharacter::MoveForwardHandler(const FInputActionValue& Value)
{
	AddMovementInput(GetActorForwardVector() * Value.Get<float>());
}

void APlayerCharacter::StrafeHandler(const FInputActionValue& Value)
{
	AddMovementInput(GetActorRightVector() * Value.Get<float>());
}

void APlayerCharacter::LookUpHandler(const FInputActionValue& Value)
{
	AddControllerPitchInput(Value.Get<float>());
}

void APlayerCharacter::TurnHandler(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<float>());
}

void APlayerCharacter::SprintHandler(const FInputActionValue& Value)
{
	isSprinting = Value.Get<bool>();
	if (isSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void APlayerCharacter::CrouchHandler(const FInputActionValue& Value)
{
	Crouch();
}

void APlayerCharacter::UnCrouchHandler(const FInputActionValue& Value)
{
	UnCrouch();
}

