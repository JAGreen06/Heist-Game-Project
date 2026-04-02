// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HeistGameMode.generated.h"

/**
 * 
 */
class ACharacterController;
class UHeistGameInstance;

UCLASS()
class HEISTGAME_API AHeistGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHeistGameMode();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void LevelComplete(bool success);

	UPROPERTY(BlueprintReadOnly)
	float ElapsedTime;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* AlarmSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Levels")
	FName NextLevelName;
	UPROPERTY()
	ACharacterController* ControllerRef;
	UPROPERTY()
	UHeistGameInstance* InstanceRef;
	
};
