// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "XCamera.h"
#include "XItem.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "XPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class XPROJECT_API AXPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AXPlayerController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	AXCamera * SetupCamera(AActor * NOwner = nullptr);

	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	AXCamera * GetCamera();

	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	AXItem * GetItemToPick();

	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	bool GetBlockInput();

	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	void SetBlockInput(bool NewBlockInput);

	UPROPERTY(EditAnywhere)
	FVector CursorLocation;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	//Move Forward
	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	void MoveForwardInput(float Value);

	//Move Right
	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	void MoveRightInput(float Value);

	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	void AddYawInput(float Value);
	
	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	void AddPitchInput(float Value);

	//Atack
	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	void StartUseHandInput();
	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	void StopUseHandInput();

	//Jump
	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	void StartJumpInput();
	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	void StopJumpInput();
	//Pickup item
	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	void PickUpItemInput();
	//Drop item
	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	void DropItemInput();
	//Set default cammera class
	UPROPERTY(EditAnywhere)
	TSubclassOf<AXCamera> CameraClass;
	//Camera ref
	UPROPERTY(EditAnywhere)
	AXCamera * CameraActor;
	//Item to pick up
	UPROPERTY(EditAnywhere)
	AXItem * SelectedItem;
	//Pick up range
	UPROPERTY(EditAnywhere)
	float PickUpRange;

	//Block input
	bool BlockInput;

	//to test some shit
	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	void TestInput();
};


