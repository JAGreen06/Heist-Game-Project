// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindAlarmLocation.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "PlayerCharacter.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"

void UBTService_FindAlarmLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AIController) { return; }
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(AIController->GetPawn());
	if (!Enemy) { return; }

	FVector AlarmLoc = Enemy->AlarmPoint[0]->GetActorLocation();

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), AlarmLoc);
}
