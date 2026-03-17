// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetGuardRotation.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"



EBTNodeResult::Type UBTTask_SetGuardRotation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AIController) { return EBTNodeResult::Failed; }
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(AIController->GetPawn());
	if (!Enemy) { return EBTNodeResult::Failed; }


	Enemy->SetActorRotation(Enemy->GuardRotation);
	AIController->SetControlRotation(Enemy->GuardRotation);

	return EBTNodeResult::Succeeded;
}
