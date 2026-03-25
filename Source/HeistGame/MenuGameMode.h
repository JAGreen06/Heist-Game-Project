// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */

class ACharacterController;

UCLASS()
class HEISTGAME_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	APawn* myPawn;

	UPROPERTY()
	ACharacterController* ControllerRef;
};
