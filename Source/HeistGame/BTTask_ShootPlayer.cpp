// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShootPlayer.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Rifle.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTTask_ShootPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(AIController->GetPawn()))
		{
			if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
			{
				FHitResult Hit;				

				FVector Start = Enemy->GetMesh()->GetSocketLocation(TEXT("RifleSocket"));
				FVector End = Start + Enemy->GetActorForwardVector() * 10000.0f;
				bool hit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);

				//Debug Line.
				FColor LineColor = hit ? FColor::Red : FColor::Green;
				DrawDebugLine(GetWorld(), Start, End, LineColor, false, 0.1f, 0, 1.0f);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
