// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetNextPatrolPoint.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_SetNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    //AIController.
    if (AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner())) // if cast succeeds
    {
        if(AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(AIController->GetPawn())) //if cast succeeds
        {
            if (Enemy->PatrolPoints.Num() > 0) //if patrol points array is populated
            { 
                AActor* NextPoint = Enemy->PatrolPoints[Enemy->index]; //Next point is set to the point at index.
                Enemy->index = (Enemy->index + 1) % Enemy->PatrolPoints.Num(); // Index is set to the next index, or loops to one if index is at end.

                FVector NextPointLocation = NextPoint->GetActorLocation(); //Get Point Location.

                OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NextPointLocation); //Sets blackboard key to point location.
                return EBTNodeResult::Succeeded;
            }
        }
    }
    return EBTNodeResult::Failed;
}
