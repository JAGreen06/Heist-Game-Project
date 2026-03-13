// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleePlayer.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


EBTNodeResult::Type UBTTask_MeleePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AIController) { return EBTNodeResult::Failed; }
	APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!PlayerChar) { return EBTNodeResult::Failed; }
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(AIController->GetPawn());
	if (!Enemy) { return EBTNodeResult::Failed; }

	//In melee range check.
	float distanceToPlayer = FVector::Dist(Enemy->GetActorLocation(), PlayerChar->GetActorLocation());
	if(distanceToPlayer >= 150.0f) { return EBTNodeResult::Failed; }
	
	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Enemy);

	FVector Start = Enemy->GetMesh()->GetSocketLocation(TEXT("RifleSocket"));
	FVector End = Start + Enemy->GetActorForwardVector() * 150.0f;
	bool hitDetected = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

	//Debug Line.
	FColor LineColor = hitDetected ? FColor::Orange : FColor::Green;
	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 0.1f, 0, 1.0f);

	if (hitDetected)
	{
		if (Hit.GetActor())
		{
			//Applys damage to the actor that has been hit.
			UGameplayStatics::ApplyDamage(Hit.GetActor(), Enemy->MeleeDamage, AIController, Enemy, UDamageType::StaticClass());
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor Melee: %s"), *Hit.GetActor()->GetName());
		}
	}

	return EBTNodeResult::Succeeded;
}