// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XSpace.h"
#include "XCapsuleSpace.generated.h"

/**
 * 
 */
UCLASS()
class XPROJECT_API AXCapsuleSpace : public AXSpace
{
	GENERATED_BODY()
public:

	AXCapsuleSpace();

		// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetRadiusDelta(float Height);

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
	void SetHeightDelta(float SpaceSize);

	UFUNCTION(BlueprintCallable)
	float GetHeightDelta();

	UFUNCTION(BlueprintCallable)
	void SetHeightMinimum(float Minimum);

	UFUNCTION(BlueprintCallable)
	float GetHeightMinimum();

	UFUNCTION(BlueprintCallable)
	void SetHeightMaximum(float Maximum);

	UFUNCTION(BlueprintCallable)
	float GetHeightMaximum();



	UFUNCTION(BlueprintCallable)
	virtual USphereComponent * GetCollisionComponent();

	//// Komponent kuli z kolizja
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UCapsuleComponent * CapsuleCollisionComponent;
	
private:

	UPROPERTY(EditAnywhere)
		float RadiusDelta;

	UPROPERTY(EditAnywhere)
		float RadiusMinimum;

	UPROPERTY(EditAnywhere)
		float RadiusMaximum;

	UPROPERTY(EditAnywhere)
		float HeightDelta;

	UPROPERTY(EditAnywhere)
		float HeightMinimum;

	UPROPERTY(EditAnywhere)
		float HeightMaximum;
};