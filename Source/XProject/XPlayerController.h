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
	
	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	void PickUpItemInput();

	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	void DropItemInput();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AXCamera> CameraClass;

	UPROPERTY(EditAnywhere)
	AXCamera * CameraActor;

	UPROPERTY(EditAnywhere)
	AXItem * ItemToPick;

	UPROPERTY(EditAnywhere)
	FVector PickUpRange;

	float ItemColdown;

	UFUNCTION(BlueprintCallable, Category = XPlayerController)
	void TestInput();
};

