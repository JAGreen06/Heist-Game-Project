// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LineOfSight.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_LineOfSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!PlayerChar) { return; }
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AIController) { return; }
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(AIController->GetPawn());
	if (!Enemy) { return; }

	FVector AIForwardVector = Enemy->GetActorForwardVector();
	FVector PlayerPositionVector = PlayerChar->GetActorLocation();
	FVector AIPositionVector = Enemy->GetActorLocation();
	FVector	AItoPlayerVector = PlayerPositionVector - AIPositionVector;
	AItoPlayerVector.Normalize();

	float distanceToPlayer = FVector::Dist(Enemy->GetActorLocation(), PlayerChar->GetActorLocation());
	float directionDotProduct = FVector::DotProduct(AItoPlayerVector, AIForwardVector);	
	
	if (AIController->LineOfSightTo(PlayerChar) && directionDotProduct > 0.5f && distanceToPlayer < 1500.0f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
		Enemy->enemyAiming = true;		
	}
	else
	{
		Enemy->enemyAiming = false;
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());	
	}
}
