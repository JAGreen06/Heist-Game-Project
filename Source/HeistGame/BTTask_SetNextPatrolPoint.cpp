// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetNextPatrolPoint.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_SetNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    //AIController.
    AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    if (!AIController) { return EBTNodeResult::Failed; }

    //Enemy Character.
    AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(AIController->GetPawn());
    if (!Enemy) { return EBTNodeResult::Failed; }

    //Make sure there are patrolPoints.
    if (Enemy->PatrolPoints.Num() == 0) { return EBTNodeResult::Failed; }

    AActor* NextPoint = Enemy->PatrolPoints[Enemy->index];
    Enemy->index = (Enemy->index + 1) % Enemy->PatrolPoints.Num();

    FVector NextPointLocation = NextPoint->GetActorLocation();

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("PatrolPoint"), NextPointLocation);

    return EBTNodeResult::Succeeded;
}
