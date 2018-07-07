// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XWeapon.h"
#include "XTwoHandWeapon.generated.h"

/**
 * 
 */
UCLASS()
class XPROJECT_API AXTwoHandWeapon : public AXWeapon
{
	GENERATED_BODY()
public:

	AXTwoHandWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnUse(class AXBaseCharacter * Character);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
