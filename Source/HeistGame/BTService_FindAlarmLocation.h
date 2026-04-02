// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_FindAlarmLocation.generated.h"

/**
 * 
 */
UCLASS()
class HEISTGAME_API UBTService_FindAlarmLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
