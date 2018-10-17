// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "XItem.h"
#include "XProjectile.h"
#include "XWeapon.generated.h"

/**
 * 
 */
UCLASS()
class XPROJECT_API AXWeapon : public AXItem
{
	GENERATED_BODY()
	
public:
	AXWeapon();

	virtual void OnUse(class AXBaseCharacter * Character);

	// Komponenty statycznej siatki 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	USkeletalMeshComponent * ActorMeshComponent;

	virtual void Tick(float DeltaTime) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
