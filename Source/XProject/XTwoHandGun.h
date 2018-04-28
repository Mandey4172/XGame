// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XTwoHandWeapon.h"
#include "XTwoHandGun.generated.h"

/**
 * 
 */
UCLASS()
class XPROJECT_API AXTwoHandGun : public AXTwoHandWeapon
{
	GENERATED_BODY()
	
public:

	AXTwoHandGun();

	UFUNCTION(BlueprintCallable)
	virtual void Use();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AXProjectile> BulletType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Offset;
};
