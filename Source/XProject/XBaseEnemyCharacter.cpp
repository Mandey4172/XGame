// Fill out your copyright notice in the Description page of Project Settings.

#include "XBaseEnemyCharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

AXBaseEnemyCharacter::AXBaseEnemyCharacter()
{
	BlackboardAsset = NewObject<UBlackboardData>();
	BehaviorTreeAsset = NewObject<UBehaviorTree>();
	this->BehaviorTreeAsset->BlackboardAsset = this->BlackboardAsset;
}

