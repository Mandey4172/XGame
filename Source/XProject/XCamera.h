// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "GameFramework/Actor.h"
#include "XCamera.generated.h"

UCLASS()
class XPROJECT_API AXCamera : public ACameraActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddPitch(float Delta);
	UFUNCTION(BlueprintCallable)
	void AddYaw(float Delta);

	UFUNCTION(BlueprintCallable)
	float GetPitch();
	UFUNCTION(BlueprintCallable)
	float GetYaw();

protected:

	UPROPERTY(EditAnywhere)
	FVector Offset;

	UPROPERTY(EditAnywhere)
	float Pitch;

	UPROPERTY(EditAnywhere)
	float Yaw;

	UPROPERTY(EditAnywhere)
	float PitchLimit;

	UPROPERTY(EditAnywhere)
	float YawLimit;
};
