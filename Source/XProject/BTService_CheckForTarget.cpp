// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_CheckForTarget.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "XBaseCharacter.h"
#include "XBaseAIController.h"

UBTService_CheckForTarget::UBTService_CheckForTarget()
{
	bCreateNodeInstance = true;
	NotyfyDistange = 500;
}

void UBTService_CheckForTarget::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	AXBaseAIController * AIController = Cast<AXBaseAIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (Character)
		{
			FVector Dif = Character->GetActorLocation() - AIController->GetPawn()->GetActorLocation();
			if (Dif.Size() <= NotyfyDistange)
			{
				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(AIController->EnemyKeyID, Character);
			}
			else
			{
				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(AIController->EnemyKeyID, nullptr);
			}
		}
	}
}