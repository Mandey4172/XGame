// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XSpace.h"
#include "XSphareSpace.generated.h"

/**
 * 
 */
UCLASS()
class XPROJECT_API AXSphareSpace : public AXSpace
{
	GENERATED_BODY()
	
public:
		
	AXSphareSpace();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetRadiusDelta(float Radius);

	UFUNCTION(BlueprintCallable)
	float GetRadiusDelta();

	UFUNCTION(BlueprintCallable)
	void SetRadiusMinimum(float Minimum);

	UFUNCTION(BlueprintCallable)
	float GetRadiusMinimum();

	UFUNCTION(BlueprintCallable)
	void SetRadiusMaximum(float Maximum);

	UFUNCTION(BlueprintCallable)
	float GetRadiusMaximum();

	UFUNCTION(BlueprintCallable)
	virtual UShapeComponent * GetCollisionComponent();

	// Komponent kuli z kolizja
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	USphereComponent * SphareCollisionComponent;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	float RadiusDelta;

	UPROPERTY(EditAnywhere)
	float RadiusMinimum;

	UPROPERTY(EditAnywhere)
	float RadiusMaximum;
	
};
