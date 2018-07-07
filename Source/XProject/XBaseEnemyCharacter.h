// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XBaseCharacter.h"
#include "XBaseEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class XPROJECT_API AXBaseEnemyCharacter : public AXBaseCharacter
{
	GENERATED_BODY()
	
public:

	AXBaseEnemyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere)
	class UBehaviorTree * BehaviorTreeAsset;

	UPROPERTY(EditAnywhere)
	class UBlackboardData * BlackboardAsset;

};
