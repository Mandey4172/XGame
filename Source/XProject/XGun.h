// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XGun.generated.h"

UCLASS()
class XPROJECT_API AXGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXGun();

	//UFUNCTION(BlueprintCallable)
	//virtual void Use(class AXBaseCharacter * Character);

	//UFUNCTION(BlueprintCallable)
	//virtual void OnUse(class AXBaseCharacter * Character);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AXProjectile> BulletType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float UseDelay;
	
};
