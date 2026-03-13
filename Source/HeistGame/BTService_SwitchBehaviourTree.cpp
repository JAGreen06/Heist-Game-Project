// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SwitchBehaviourTree.h"
#include "EnemyAIController.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"


void UBTService_SwitchBehaviourTree::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!PlayerChar) { return; }
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AIController) { return; }
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(AIController->GetPawn());
	if (!Enemy) { return; }

	bool playerVisible = OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	
	//Runs at the top of each tree anyway so check for dead in here.
	if (Enemy->isDead)
	{
		AIController->GetBrainComponent()->StopLogic("Dead");
		AIController->StopMovement();
		Enemy->enemyAiming = false;
		return;
	}


	if ((playerVisible && !Enemy->isAgressive))
	{
		Enemy->isAgressive = true;			
		AIController->SwitchBehaviourTree(AIController->AgressiveBehaviourTree);
	}
	if(!playerVisible && Enemy->isAgressive)
	{
		bool lastKnownLocation = OwnerComp.GetBlackboardComponent()->IsVectorValueSet(TEXT("LastKnownLocation"));

		if (!lastKnownLocation)
		{
			Enemy->isAgressive = false;
			AIController->ClearFocus(EAIFocusPriority::Gameplay);
			AIController->SwitchBehaviourTree(AIController->DefaultBehaviourTree);
		}
	}

}
