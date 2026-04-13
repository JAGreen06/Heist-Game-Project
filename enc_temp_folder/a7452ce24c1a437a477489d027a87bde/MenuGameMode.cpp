// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterController.h"

void AMenuGameMode::BeginPlay()
{
	ControllerRef = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));

	myPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	myPawn->DisableInput(ControllerRef);
}
