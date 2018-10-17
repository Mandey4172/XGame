// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "XBaseCharacter.h"
#include "XPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class XPROJECT_API AXPlayerCharacter : public AXBaseCharacter
{
	GENERATED_BODY()

public:

	AXPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	////Move Forward
	//UFUNCTION(BlueprintCallable)
	//	void MoveForwardInput(float Value);

	////Move Right
	//UFUNCTION(BlueprintCallable)
	//	void MoveRightInput(float Value);

	////
	//UFUNCTION(BlueprintCallable)
	//	void AddYawInput(float Value);

	//UFUNCTION(BlueprintCallable)
	//	void AddPitchInput(float Value);

	////Atack
	//UFUNCTION(BlueprintCallable)
	//	void StartUseHandInput();
	//UFUNCTION(BlueprintCallable)
	//	void StopUseHandInput();

	////Jump
	//UFUNCTION(BlueprintCallable)
	//	void StartJumpInput();
	//UFUNCTION(BlueprintCallable)
	//	void StopJumpInput();

	//Pickup item
	UFUNCTION(BlueprintCallable)
		void PickUpItemInput();
	//Drop item
	UFUNCTION(BlueprintCallable)
		void DropItemInput();
};
