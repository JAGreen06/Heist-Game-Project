// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"


class ARifle;

UCLASS()
class HEISTGAME_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

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

	UPROPERTY()
	AActor* Weapon;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ARifle> RifleClass;


	UPROPERTY(EditAnywhere, Category = "Health")
	float EnemyHealth = 100.0f;

public:
	UPROPERTY(EditInstanceOnly) //Allows each individual enemy to have its own designated patrol points.
	TArray<AActor*> PatrolPoints;
	UPROPERTY()
	int index;

	UPROPERTY(BlueprintReadOnly)
	bool isDead = false;
	UPROPERTY(BlueprintReadOnly)
	bool enemyAiming = false;
	UPROPERTY()
	bool isAgressive = false;	

	float ShotDamage = 10.0f;	
	float MeleeDamage = 5.0f;
};
