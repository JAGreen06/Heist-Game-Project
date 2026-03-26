// Fill out your copyright notice in the Description page of Project Settings.


#include "HeistGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterController.h"

AHeistGameMode::AHeistGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AHeistGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;
	//UE_LOG(LogTemp, Warning, TEXT("Time: %f"), ElapsedTime);
}

void AHeistGameMode::BeginPlay()
{
	Super::BeginPlay();
	ControllerRef = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
}


void AHeistGameMode::LevelComplete(bool success)
{
	if (success)
	{
		UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
	}
	else
	{
		if (!ControllerRef) { return; };
		ControllerRef->SetUIState(GameUIState::Fail);
	}
}




