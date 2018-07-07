// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "XSpace.generated.h"

UCLASS()
class XPROJECT_API AXSpace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXSpace();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	float GetDamage();

	UFUNCTION(BlueprintCallable)
	virtual void OnCollision(AActor * OtherActor, const FHitResult & SweepResult);

	UFUNCTION(BlueprintCallable)
	virtual UShapeComponent * GetCollisionComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float Damage;

private:

};
