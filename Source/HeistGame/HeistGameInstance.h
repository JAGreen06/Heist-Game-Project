// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HeistGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HEISTGAME_API UHeistGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	float banklevelTime = 0.0f;
	UPROPERTY(BlueprintReadOnly)
	float towerLevelTime = 0.0f;
	UPROPERTY(BlueprintReadOnly)
	float MilitaryBaseTime = 0.0f;
};
