// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;

class ARifle;
class ACharacterController;
class AHeistGameMode;

UCLASS()
class HEISTGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Weapon Variables.
	UPROPERTY()
	AActor* Weapon;
	UPROPERTY(EditDefaultsOnly, Category = "Rifle")
	TSubclassOf<ARifle> RifleClass;


	//Camera and ADS variables.
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float zoomFOV = 65.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float defaultFOV = 90.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float interpSpeed = 10.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float defaultArmLength = 300.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float zoomArmLength = 150.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	FVector DefaultOffset = FVector(0.0f, 70.0f, 70.0f);
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	FVector ZoomOffset = FVector(0.0f, 50.0f, 70.0f);
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ADSAction;

	//Pause input.
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* PauseAction;

	//Movement inputs.
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* characterMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveForwardAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* StrafeAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* TurnAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookUpAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* SprintAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* CrouchAction;


	//Sprint Variables.
	UPROPERTY(EditDefaultsOnly, Category = "Sprinting")
	float WalkSpeed = 600.f;
	UPROPERTY(EditDefaultsOnly, Category = "Sprinting")
	float SprintSpeed = 1000.f;
	UPROPERTY(EditDefaultsOnly, Category = "Sprinting")
	bool isSprinting;
	float SprintDrain = 0.5f;
	void  StaminaDrain();
	

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* FireAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ReloadAction;


	bool isCarryingJewel = false;

	
	UPROPERTY()
	ACharacterController* ControllerRef;
	UPROPERTY()
	AHeistGameMode* GamemodeRef;


	UPROPERTY(EditDefaultsOnly, Category = "Timer")
	float deathTimeOffset = 2.0f;

	UPROPERTY()
	FTimerHandle DeathTimer;
	UFUNCTION()
	void PlayerDeath();
	float deathFOV = 1000.0f;


	//Player Shooting.
	UPROPERTY()
	FHitResult Hit;
	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	int maxShots = 20;	
	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	float shotDamage = 10.0f;
	float castRange = 10000.0f;
	FVector cameraLocation;
	FRotator cameraRotation;
	bool hitDetected;


	//Pause Handling.
	void PauseHandler(const FInputActionValue& Value);

	//Movement Handling.
	void MoveForwardHandler(const FInputActionValue& Value);
	void StrafeHandler(const FInputActionValue& Value);
	void LookUpHandler(const FInputActionValue& Value);
	void TurnHandler(const FInputActionValue& Value);
	void SprintHandler(const FInputActionValue& Value);

	//Crouch Handling.
	void CrouchHandler(const FInputActionValue& Value);
	void UnCrouchHandler(const FInputActionValue& Value);

	//Aim / Shooting Handling.
	void AimHandler(const FInputActionValue& Value);
	void AimDownSight(float& DeltaTime);
	void FireHandler();
	void ReloadHandler(const FInputActionValue& Value);
public:

	//Jewel Carrying.
	void SetCarryingJewel(bool isCarrying) { isCarryingJewel = isCarrying; }

	UFUNCTION(BlueprintCallable)
	bool GetCarryingJewel() { return isCarryingJewel; }

	//Shot Count.
	UPROPERTY(BlueprintReadOnly)
	int shotCount = maxShots;

	//Player ADS.
	UPROPERTY(BlueprintReadOnly)
	bool isAiming;

	//Player Dead.
	UPROPERTY(BlueprintReadOnly)
	bool PlayerDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	float PlayerHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	float SprintAmount = 100.0f;
};
