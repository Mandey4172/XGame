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

	//Call to damage character 
	UFUNCTION(BlueprintCallable)
	virtual void InflictDamage(float DamageAmount, const FHitResult& Hit);

	//Take damage . This method change Hit Points of Character
	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

	//Heal damage.
	UFUNCTION(BlueprintCallable)
	virtual float HealDamage(float HealAmount);


	UFUNCTION(BlueprintCallable)
	float GetHealth();

	//Kill character 
	UFUNCTION(BlueprintCallable)
	virtual void Kill();

	//Use item
	UFUNCTION(BlueprintCallable)
	virtual void UseItem(AXItem * Item);
	
	//Pick up item
	UFUNCTION(BlueprintCallable)
	virtual void PickUpItem(AXItem * Item);

	//Drop item
	UFUNCTION(BlueprintCallable)
	virtual void DropItem(AXItem * Item, int Amount = 0);

	//Equip weapons methods
	//Equip two hand weapons
	UFUNCTION(BlueprintCallable)
	virtual void EquipTwoHandWeapon(AXTwoHandWeapon * Weapon);

	//Equip one hand weapons
	UFUNCTION(BlueprintCallable)
	virtual void EquipOneHandWeapon(AXOneHandWeapon * MainWeapon, AXOneHandWeapon * OffWeapon = nullptr);

	//Unequip all equped weapons
	UFUNCTION(BlueprintCallable)
	virtual void UnequipWeapon();
	
	//Called when character begin overlap with other actor 
	UFUNCTION(BlueprintCallable)
	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	//Get Backpack of character
	UFUNCTION(BlueprintCallable)
	TArray<AXItem *> GetBackpack();

	//Get Maximum health
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth();

	//Set Maximum health
	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float MaxHealth);

	//Get weapon in right hand (when two hand weapon right hadn == left hand)
	UFUNCTION(BlueprintCallable)
	AXWeapon * GetRightHandWeapon();

	//Get weapon in left hand
	UFUNCTION(BlueprintCallable)
	AXWeapon * GetLeftHandWeapon();

	//Pitch of aim
	float AimPitch;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game destroys actor
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

	//Weapon
	UPROPERTY(VisibleAnywhere)
	AXWeapon * LeftHandWeapon;

	UPROPERTY(VisibleAnywhere)
	AXWeapon * RightHandWeapon;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AXWeapon> LeftHandWeaponClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AXWeapon> RightHandWeaponClass;

	//Backpack of items
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
};
