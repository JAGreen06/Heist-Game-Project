// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"
/**
 * 
 */

class AExtractionPoint;

UCLASS()
class HEISTGAME_API ACharacterController : public APlayerController
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY()
	UUserWidget* HUD;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ExtractionTimeClass;
	UPROPERTY()
	UUserWidget* EXTRACTIONTIME;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> NextLevelClass;
	UPROPERTY()
	UUserWidget* NEXT;




	UPROPERTY()
	FTimerHandle ExtractionTimeLeft;

	UFUNCTION(BlueprintPure)
	float GetTimeTillExtract();

public:

	void ShowNextLevelScreen();

	UPROPERTY()
	AExtractionPoint* ExtractionRef;
};
