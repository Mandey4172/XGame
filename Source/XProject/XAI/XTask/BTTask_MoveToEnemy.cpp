// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_MoveToEnemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "XBaseAIController.h"
#include "XBaseCharacter.h"
UBTTask_MoveToEnemy::UBTTask_MoveToEnemy()
{
	Distance = 50.f;
}

EBTNodeResult::Type UBTTask_MoveToEnemy::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AXBaseAIController * AIController = Cast<AXBaseAIController>(OwnerComp.GetAIOwner());
	AXBaseCharacter *  Enemy = Cast<AXBaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(AIController->EnemyKeyID));

	if (Enemy)
	{
		AIController->MoveToActor(Enemy, Distance, true, true, true, 0, true);
		return EBTNodeResult::Succeeded;
	}
	/*if (Enemy &&  AIController)
	{
		AIController->MoveToActor(Enemy, 5.f, true, true, true, 0, true);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Moving");
		return EBTNodeResult::Succeeded;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Not moving");
	}*/
	return EBTNodeResult::Failed;
}
