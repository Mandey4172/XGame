// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "GameFramework/Actor.h"
#include "XSphareSpace.h"
#include "XProjectile.generated.h"

UCLASS()
class XPROJECT_API AXProjectile : public AXSphareSpace
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable)
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION(BlueprintCallable)
	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION(BlueprintCallable)
	virtual void OnCollision(AActor * OtherActor, const FHitResult & SweepResult);
	
	// Komponenty poruszania sie pocisku 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UProjectileMovementComponent * ProjectileMovementComponent;

	// Komponenty statycznej siatki 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent * ActorMeshComponent;

protected:

};
