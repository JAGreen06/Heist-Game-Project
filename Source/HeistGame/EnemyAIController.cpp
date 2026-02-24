// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyCharacter.h"

#include "Engine/TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APawn* AIPawn = GetPawn();

	FVector AIForwardVector = AIPawn->GetActorForwardVector();
	FVector PlayerPositionVector = PlayerPawn->GetActorLocation();
	FVector AIPositionVector = AIPawn->GetActorLocation();
	FVector	AItoPlayerVector = PlayerPositionVector - AIPositionVector;
	AItoPlayerVector.Normalize();

	float directionDotProduct = FVector::DotProduct(AItoPlayerVector, AIForwardVector);

	if (AController::LineOfSightTo(PlayerPawn) && directionDotProduct > 0)
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AEnemyCharacter* enemy = Cast<AEnemyCharacter>(GetPawn());
	AActor* point = enemy->GetPatrolPoint();
	FVector pointPos = point->GetActorLocation();


	if (EnemyBehaviourTree != nullptr)
	{
		RunBehaviorTree(EnemyBehaviourTree);
	}

	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPoint"), pointPos);
	}
}

void AEnemyAIController::Patrol()
{
	AEnemyCharacter* enemy = Cast<AEnemyCharacter>(GetPawn());
	if (enemy)
	{
		AActor* point = enemy->GetPatrolPoint();
		MoveToActor(point, 10.0f);
	}
}
