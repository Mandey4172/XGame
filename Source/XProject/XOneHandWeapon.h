// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XWeapon.h"
#include "XOneHandWeapon.generated.h"

/**
 * 
 */
UCLASS()
class XPROJECT_API AXOneHandWeapon : public AXWeapon
{
	GENERATED_BODY()

public:
	AXOneHandWeapon();	

	UFUNCTION(BlueprintCallable)
	virtual void Use();

	UFUNCTION(BlueprintCallable)
	virtual void SetIsRightHand(bool RightHand);
	UFUNCTION(BlueprintCallable)
	bool IsRightHand();

protected:

	bool RightHand;
};
