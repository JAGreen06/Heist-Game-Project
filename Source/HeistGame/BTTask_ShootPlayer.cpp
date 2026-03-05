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

				FCollisionQueryParams Params;
				Params.AddIgnoredActor(Enemy);

				FVector Start = Enemy->GetMesh()->GetSocketLocation(TEXT("RifleSocket"));
					
				FVector End = Start + Enemy->GetActorForwardVector() * 10000.0f;
				bool hitDetected = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

				//Debug Line.
				FColor LineColor = hitDetected ? FColor::Red : FColor::Green;
				DrawDebugLine(GetWorld(), Start, End, LineColor, false, 0.1f, 0, 1.0f);

				if (hitDetected)
				{
					if (Hit.GetActor())
					{
						//Applys damage to the actor that has been hit.
						UGameplayStatics::ApplyDamage(Hit.GetActor(), Enemy->enemyShotDamage, AIController, Enemy, UDamageType::StaticClass());
						UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *Hit.GetActor()->GetName());
					}
				}

				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
