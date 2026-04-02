// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SoundAlarm.h"
#include "HeistGameMode.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_SoundAlarm::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AHeistGameMode* gamemodeRef = Cast<AHeistGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!gamemodeRef) { return EBTNodeResult::Failed; }

	UGameplayStatics::PlaySound2D(GetWorld(), gamemodeRef->AlarmSound, 1.0f, 1.0f, 0.0f);

	gamemodeRef->LevelComplete(false);
	return EBTNodeResult::Succeeded;
}
