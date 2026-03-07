// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HeistGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HEISTGAME_API AHeistGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void LevelComplete(bool success);

	UPROPERTY(EditAnywhere, Category = "Levels")
	FName NextLevelName;
private:
};
