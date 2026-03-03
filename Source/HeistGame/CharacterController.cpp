// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "Blueprint/UserWidget.h"

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		HUD = CreateWidget(this, HUDWidgetClass);
		if (HUD) { HUD->AddToViewport(); }
	}
}
