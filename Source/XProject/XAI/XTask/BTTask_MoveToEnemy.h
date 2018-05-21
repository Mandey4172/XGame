// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToEnemy.generated.h"

/**
 * 
 */
UCLASS()
class XPROJECT_API UBTTask_MoveToEnemy : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_MoveToEnemy();

	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere)
	float Distance;
};
