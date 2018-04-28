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

	UFUNCTION(BlueprintCallable)
	virtual void Use();
};
