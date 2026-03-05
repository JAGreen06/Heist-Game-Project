// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"
/**
 * 
 */

class UBlackboardComponent;

UCLASS()
class HEISTGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* EnemyBehaviourTree;

};
