// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "XSpace.h"
#include "XBoxSpace.generated.h"

/**
 * 
 */
UCLASS()
class XPROJECT_API AXBoxSpace : public AXSpace
{
	GENERATED_BODY()
	
public:

	AXBoxSpace();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetSpaceSizeDelta(FVector SpaceSize);

	UFUNCTION(BlueprintCallable)
	FVector GetSpaceSizeDelta();

	UFUNCTION(BlueprintCallable)
	void SetSpaceSizeMinimum(FVector Minimum);

	UFUNCTION(BlueprintCallable)
	FVector GetSpaceSizeMinimum();

	UFUNCTION(BlueprintCallable)
	void SetSpaceSizeMaximum(FVector Maximum);

	UFUNCTION(BlueprintCallable)
	FVector GetSpaceSizeMaximum();

	UShapeComponent * GetCollisionComponent() override;

	//// Komponent kuli z kolizja
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UBoxComponent * BoxCollisionComponent;
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	FVector SpaceSizeDelta;

	UPROPERTY(EditAnywhere)
	FVector SpaceSizeMinimum;

	UPROPERTY(EditAnywhere)
	FVector SpaceSizeMaximum;
};
