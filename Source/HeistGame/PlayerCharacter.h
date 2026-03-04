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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly)
	bool isAiming;

private:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;


	UPROPERTY()
	AActor* Weapon;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ARifle> RifleClass;

	UPROPERTY(EditAnywhere)
	float zoomFOV = 65.0f;
	UPROPERTY(EditAnywhere)
	float defaultFOV = 90.0f;
	UPROPERTY(EditAnywhere)
	float interpSpeed = 10.0f;
	UPROPERTY(EditAnywhere)
	float defaultArmLength = 300.0f;
	UPROPERTY(EditAnywhere)
	float zoomArmLength = 150.0f;
	UPROPERTY(EditAnywhere)
	FVector DefaultOffset = FVector(0.0f, 70.0f, 70.0f);
	UPROPERTY(EditAnywhere)
	FVector ZoomOffset = FVector(0.0f, 50.0f, 70.0f);
	UPROPERTY(EditAnywhere)
	UInputAction* ADSAction;


	UPROPERTY(EditAnywhere)
	UInputMappingContext* characterMappingContext;
	UPROPERTY(EditAnywhere)
	UInputAction* MoveForwardAction;
	UPROPERTY(EditAnywhere)
	UInputAction* StrafeAction;
	UPROPERTY(EditAnywhere)
	UInputAction* TurnAction;
	UPROPERTY(EditAnywhere)
	UInputAction* LookUpAction;
	UPROPERTY(EditAnywhere)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere)
	UInputAction* SprintAction;
	UPROPERTY(EditAnywhere)
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere)
	float WalkSpeed = 600.f;

	UPROPERTY(EditAnywhere)
	float SprintSpeed = 1000.f;

	UPROPERTY(EditAnywhere)
	bool isSprinting;
	
	UPROPERTY(EditAnywhere)
	UInputAction* FireAction;


	UPROPERTY()
	bool isCarryingJewel = false;


	//Movement Handler Functions
	void MoveForwardHandler(const FInputActionValue& Value);
	void StrafeHandler(const FInputActionValue& Value);
	void LookUpHandler(const FInputActionValue& Value);
	void TurnHandler(const FInputActionValue& Value);
	void SprintHandler(const FInputActionValue& Value);

	void CrouchHandler(const FInputActionValue& Value);
	void UnCrouchHandler(const FInputActionValue& Value);

	void AimHandler(const FInputActionValue& Value);
	void FireHandler();
	void AimDownSight(float& DeltaTime);

public:
	void SetCarryingJewel(bool isCarrying);
	UFUNCTION(BlueprintCallable)
	bool GetCarryingJewel();
};
