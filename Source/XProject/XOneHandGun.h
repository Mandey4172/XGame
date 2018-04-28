// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XOneHandWeapon.h"
#include "XOneHandGun.generated.h"

/**
 * 
 */
UCLASS()
class XPROJECT_API AXOneHandGun : public AXOneHandWeapon
{
	GENERATED_BODY()
	
public:
	AXOneHandGun();

	UFUNCTION(BlueprintCallable)
	virtual void Use();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AXProjectile> BulletType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Offset;
};
