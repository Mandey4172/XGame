// Fill out your copyright notice in the Description page of Project Settings.

#include "XBaseAIController.h"
#include "XBaseEnemyCharacter.h"
/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


AXBaseAIController::AXBaseAIController( const class FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
{
	BehaviorTreeComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this,TEXT("Behavior Tree Component"));
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("Blackboard Component"));
}

void AXBaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXBaseAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AXBaseAIController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);

	AXBaseEnemyCharacter * AICharacter = Cast<AXBaseEnemyCharacter>(InPawn);

	if (AICharacter)
	{
		if (AICharacter->BehaviorTreeAsset)
		{
			if (AICharacter->BehaviorTreeAsset->BlackboardAsset)
			{
				BlackboardComp->InitializeBlackboard(*AICharacter->BehaviorTreeAsset->BlackboardAsset);
				EnemyKeyID = BlackboardComp->GetKeyID("Target");
			}
			BehaviorTreeComp->StartTree(*AICharacter->BehaviorTreeAsset);
		}
	}
}

void AXBaseAIController::UnPossess()
{
	Super::UnPossess();

	BehaviorTreeComp->StopTree();
}