// Fill out your copyright notice in the Description page of Project Settings.


#include "HeistGameMode.h"
#include "Kismet/GameplayStatics.h"

void AHeistGameMode::LevelComplete(bool success)
{
	if (success)
	{
		UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
	}
	else
	{
		//Show a fail level screen, retry, quit etc.
	}
}
