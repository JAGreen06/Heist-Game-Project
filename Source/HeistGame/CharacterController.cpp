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

	if (FailLevelClass)
	{
		FAIL = CreateWidget(this, FailLevelClass);
	}

	if (MenuLevelClass)
	{
		MENU = CreateWidget(this, MenuLevelClass);
	}

	if (LevelSelectClass)
	{
		LEVELSELECT = CreateWidget(this, LevelSelectClass);
	}

	if (UGameplayStatics::GetCurrentLevelName(this) == "MenuLevel")
	{
		SetUIState(GameUIState::MainMenu);
	}
	else
	{
		SetUIState(GameUIState::Game);
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

void ACharacterController::FailLevelScreen()
{
	if (FAIL) { FAIL->AddToViewport(); }

	SetShowMouseCursor(true);
	SetPause(true);
}

void ACharacterController::SetUIState(GameUIState nextState)
{	
	if (HUD) HUD->RemoveFromViewport();
	if (MENU) MENU->RemoveFromViewport();
	if (LEVELSELECT) LEVELSELECT->RemoveFromViewport();

	switch (nextState)
	{
	case GameUIState::MainMenu:
	{
		if (MENU) { MENU->AddToViewport(); }
		SetShowMouseCursor(true);
		break;
	}
	case GameUIState::LevelSelect:
	{
		if (LEVELSELECT) { LEVELSELECT->AddToViewport(); }
		SetShowMouseCursor(true);
		break;
	}	
	case GameUIState::Game:
	{
		if (HUD) { HUD->AddToViewport(); }
		SetShowMouseCursor(false);
		break;
	}
	}
}
