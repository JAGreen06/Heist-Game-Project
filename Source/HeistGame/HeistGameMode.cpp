// Fill out your copyright notice in the Description page of Project Settings.


#include "HeistGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterController.h"
#include "HeistGameInstance.h"

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
	InstanceRef = Cast<UHeistGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}


void AHeistGameMode::LevelComplete(bool success)
{
	if (success)
	{
		if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "BankLevel")
		{
			InstanceRef->banklevelTime = ElapsedTime;
		}
		if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "TowerLevel")
		{
			InstanceRef->towerLevelTime = ElapsedTime;
		}
		if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "MilitaryLevel")
		{
			InstanceRef->MilitaryBaseTime = ElapsedTime;
		}
		UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
	}
	else
	{
		if (!ControllerRef) { return; };
		ControllerRef->SetUIState(GameUIState::Fail);
	}
}




