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
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsObject(TEXT("TargetPlayer"), PlayerPawn);
		GetBlackboardComponent()->SetValueAsBool(TEXT("PlayerVisible"), true);
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("TargetPlayer"));
		GetBlackboardComponent()->SetValueAsBool(TEXT("PlayerVisible"), false);
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

	if (EnemyBehaviourTree != nullptr)
	{
		RunBehaviorTree(EnemyBehaviourTree);
	}
}

