// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "XBaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class XPROJECT_API AXBaseAIController : public AAIController
{
	GENERATED_BODY()
public:

	AXBaseAIController(const class FObjectInitializer& ObjectInitializer );

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UBlackboardComponent * BlackboardComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UBehaviorTreeComponent * BehaviorTreeComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	uint8 EnemyKeyID;


private:
	/* Called whenever the controller possesses a character bot */
	virtual void Possess(class APawn* InPawn) override;

	virtual void UnPossess() override;
};
