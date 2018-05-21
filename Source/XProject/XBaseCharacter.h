// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "XItem.h"
#include "XWeapon.h"
#include "XTwoHandWeapon.h"
#include "XOneHandWeapon.h"
#include "XBaseCharacter.generated.h"

UCLASS()
class XPROJECT_API AXBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AXBaseCharacter();
//	void set();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Move Forward
	UFUNCTION(BlueprintCallable)
	void MoveForward(float Value);

	//Move Right
	UFUNCTION(BlueprintCallable)
	void MoveRight(float Value);
	
	//Atack
	UFUNCTION(BlueprintCallable)
	void StartUseHand();
	void StopUseHand();

	//Jump
	UFUNCTION(BlueprintCallable)
	void StartJump();
	UFUNCTION(BlueprintCallable)
	void StopJump();

	UFUNCTION(BlueprintCallable)
	virtual void InflictDamage(float DamageAmount, const FHitResult& Hit);

	//
	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

	UFUNCTION(BlueprintCallable)
	virtual float HealDamage(float HealAmount);

	UFUNCTION(BlueprintCallable)
	float GetHealth();

	UFUNCTION(BlueprintCallable)
	virtual void Kill();

	UFUNCTION(BlueprintCallable)
	virtual void UseItem(AXItem * Item);
	
	UFUNCTION(BlueprintCallable)
	virtual void PickUpItem(AXItem * Item);

	UFUNCTION(BlueprintCallable)
	virtual void DropItem(AXItem * Item, int Amount = 0);

	UFUNCTION(BlueprintCallable)
	virtual void EquipTwoHandWeapon(AXTwoHandWeapon * Weapon);

	UFUNCTION(BlueprintCallable)
	virtual void EquipOneHandWeapon(AXOneHandWeapon * MainWeapon, AXOneHandWeapon * OffWeapon = nullptr);

	UFUNCTION(BlueprintCallable)
	virtual void UnequipWeapon();
	
	UFUNCTION(BlueprintCallable)
	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable)
	TArray<AXItem *> GetBackpack();

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float MaxHealth);

	UFUNCTION(BlueprintCallable)
	AXWeapon * GetRightHandWeapon();

	UFUNCTION(BlueprintCallable)
	AXWeapon * GetLeftHandWeapon();

	float AimPitch;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Weapon
	UPROPERTY(EditAnywhere)
	AXWeapon * LeftHandWeapon;

	UPROPERTY(EditAnywhere)
	AXWeapon * RightHandWeapon;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AXWeapon> LeftHandWeaponClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AXWeapon> RightHandWeaponClass;

	UPROPERTY(EditAnywhere)
	TArray<AXItem *> Backpack;
	
	UPROPERTY(EditAnywhere)
	float MaxHealth;
	//
	UPROPERTY(EditAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	FVector DropOffset;

	bool IsJumping;
	bool IsUsingRightHand;
	bool IsUsingLeftHand;

	float RightHandBlockTime;
	float LeftHandBlockTime;
};
