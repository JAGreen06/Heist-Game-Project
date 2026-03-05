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
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(AIController->GetPawn());

	FVector AIForwardVector = Enemy->GetActorForwardVector();
	FVector PlayerPositionVector = PlayerChar->GetActorLocation();
	FVector AIPositionVector = Enemy->GetActorLocation();
	FVector	AItoPlayerVector = PlayerPositionVector - AIPositionVector;
	AItoPlayerVector.Normalize();

	float directionDotProduct = FVector::DotProduct(AItoPlayerVector, AIForwardVector);

	if (AIController->LineOfSightTo(PlayerChar) && directionDotProduct > 0)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}
