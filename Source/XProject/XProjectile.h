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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	void FireInDirection(const FVector& ShootDirection);

	virtual void OnCollision(AActor * OtherActor, const FHitResult & SweepResult) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//	
	UFUNCTION(BlueprintCallable)
	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	

	// Komponenty poruszania sie pocisku 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UProjectileMovementComponent * ProjectileMovementComponent;

	// Komponenty statycznej siatki 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent * ActorMeshComponent;

protected:

};
