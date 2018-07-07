// Fill out your copyright notice in the Description page of Project Settings.

#include "XBaseEnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

AXBaseEnemyCharacter::AXBaseEnemyCharacter()
{
	BlackboardAsset = NewObject<UBlackboardData>();
	BehaviorTreeAsset = NewObject<UBehaviorTree>();
	BehaviorTreeAsset->BlackboardAsset = BlackboardAsset;
}

void AXBaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXBaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}
