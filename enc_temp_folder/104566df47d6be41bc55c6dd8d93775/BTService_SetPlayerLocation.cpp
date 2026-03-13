// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetPlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "PlayerCharacter.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"

void UBTService_SetPlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{		
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AIController) { return; }
	APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!PlayerChar) { return; }
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(AIController->GetPawn());
	if (!Enemy) { return; }

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerChar);	

	float Distance = FVector::Dist(Enemy->GetActorLocation(), PlayerChar->GetActorLocation());
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("DistanceToPlayer"), Distance);
}
