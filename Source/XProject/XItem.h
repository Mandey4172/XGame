// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"

#include "XItem.generated.h"

UCLASS()
class XPROJECT_API AXItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXItem();

	UFUNCTION(BlueprintCallable)
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Use(class AXBaseCharacter * Character);

	UFUNCTION(BlueprintCallable)
	virtual void OnUse(class AXBaseCharacter * Character);

	UFUNCTION(BlueprintCallable)
	bool IsStackable();

	UFUNCTION(BlueprintCallable)
	int GetStackSize();

	UFUNCTION(BlueprintCallable)
	int GetStackMaximalSize();

	UFUNCTION(BlueprintCallable)
	void AddToStack(int Val);
	//UFUNCTION(BlueprintCallable)
	//	void OnPick();

	//UFUNCTION(BlueprintCallable)
	//	void OnDrop();

	/* Komponent kuli z kolizja */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UShapeComponent * CollisionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	bool bIsStackable;

	UPROPERTY(EditAnywhere)
	int StackSize;

	UPROPERTY(EditAnywhere)
	int StackMaximalSize;

	UPROPERTY(EditAnywhere)
	float OnUseColdown;

protected:
	UPROPERTY(EditAnywhere)
	float Coldown;

};
