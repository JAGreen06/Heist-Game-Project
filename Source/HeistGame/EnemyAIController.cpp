// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(GetPawn()))
	{
		if (Enemy->isDead || !Enemy->enemyAiming)
		{
			ClearFocus(EAIFocusPriority::Gameplay);
			return;
		}
		if (Enemy->enemyAiming && PlayerChar)
		{
			SetFocus(PlayerChar);
		}
	}
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (EnemyBehaviourTree != nullptr)
	{
		RunBehaviorTree(EnemyBehaviourTree);
		
		BlackboardComp = GetBlackboardComponent();
	}
		
	
}

