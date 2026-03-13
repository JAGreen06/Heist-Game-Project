// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SwitchBehaviourTree.generated.h"

/**
 * 
 */
UCLASS()
class HEISTGAME_API UBTService_SwitchBehaviourTree : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
