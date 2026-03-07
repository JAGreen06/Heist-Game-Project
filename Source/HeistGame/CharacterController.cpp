// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ExtractionPoint.h"

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		HUD = CreateWidget(this, HUDWidgetClass);
		if (HUD) { HUD->AddToViewport(); }
	}

	if (ExtractionTimeClass)
	{
		EXTRACTIONTIME = CreateWidget(this, ExtractionTimeClass);
		if (EXTRACTIONTIME) { EXTRACTIONTIME->AddToViewport(); }
	}

	if (NextLevelClass)
	{
		NEXT = CreateWidget(this, NextLevelClass);		
	}

}

float ACharacterController::GetTimeTillExtract()
{
	if (!ExtractionRef) { 
		return 0.0f; 
	}

	ExtractionRef->GetExtractionTimer(ExtractionTimeLeft);
	return GetWorld()->GetTimerManager().GetTimerRemaining(ExtractionTimeLeft);
}

void ACharacterController::ShowNextLevelScreen()
{
	if (EXTRACTIONTIME) { EXTRACTIONTIME->RemoveFromViewport(); }

	if (NEXT) { NEXT->AddToViewport(); }

	SetShowMouseCursor(true);
	SetPause(true);
}
