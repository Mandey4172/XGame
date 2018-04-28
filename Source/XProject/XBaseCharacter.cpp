// Fill out your copyright notice in the Description page of Project Settings.

#include "XBaseCharacter.h"
#include "XPlayerController.h"
#include "XProjectile.h"
#include "XSpace.h"

#include <EngineMinimal.h>

#include "Kismet/GameplayStatics.h"

// Sets default values
AXBaseCharacter::AXBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/MyMesh.MyMesh"));
	this->IsJumping = false;
	this->IsUsingHands = false;

	// Czy character ma wywowylac metode Tick()
	PrimaryActorTick.bCanEverTick = true;

	this->GetCapsuleComponent()->bGenerateOverlapEvents = true;
	this->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&AXBaseCharacter::BeginOverlap);
	
	Health = 100.f;
	CharacterBlockTime = 0.f;
	AimPitch = 0.f;

	DropOffset = FVector(100.f,0.f,0.f);
}

// Called when the game starts or when spawned
void AXBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AXPlayerController * PC = Cast<AXPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PC)
	{
		AActor * NewCamera = Cast<AActor>(PC->SetupCamera(this));
		if (NewCamera)
		{
			PC->SetViewTarget(NewCamera);
		}	
		//AXTwoHandWeapon * TwoHand = Cast<AXTwoHandWeapon>(RightHandWeapon);
		//AXOneHandWeapon * MainHand = Cast<AXOneHandWeapon>(RightHandWeapon);
		//AXOneHandWeapon * OffHand = Cast<AXOneHandWeapon>(LeftHandWeapon);
		//if (TwoHand)
		//	EquipTwoHandWeapon(TwoHand);
		//else
		//	EquipOneHandWeapon(MainHand, OffHand);
		//EquipWeapon(RightHandWeapon);
	}
	UWorld* World = GetWorld();
	if (World)
	{
		//Parametry dodawania postaci do gry
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		bool IsOneHand = true;
		AXWeapon * RWeapon = World->SpawnActor<AXWeapon>(this->RightHandWeaponClass, SpawnParams);
		AXWeapon * LWeapon = World->SpawnActor<AXWeapon>(this->LeftHandWeaponClass, SpawnParams);

		if (Cast<AXTwoHandWeapon>(RWeapon))
		{
			IsOneHand = false;
		}
		if(RWeapon) RWeapon->Destroy();
		if (Cast<AXTwoHandWeapon>(LWeapon))
		{
			IsOneHand = false;
		}
		if(LWeapon) LWeapon->Destroy();
		if (IsOneHand)
			EquipOneHandWeapon(nullptr);
		else
			EquipTwoHandWeapon(nullptr);
	}
}

// Called every frame
void AXBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsUsingHands && (CharacterBlockTime <= 0))
	{
		if (RightHandWeapon && LeftHandWeapon == RightHandWeapon)
		{
			RightHandWeapon->Use();
		}
		else
		{
			if (RightHandWeapon)
			{
				RightHandWeapon->Use();
			}
			if (LeftHandWeapon)
			{
				LeftHandWeapon->Use();
			}
		}
		CharacterBlockTime = 0.4;
	}
	if (CharacterBlockTime > 0)
	{
		CharacterBlockTime -= DeltaTime;
	}
}

// Called to bind functionality to input
void AXBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
}

void AXBaseCharacter::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = GetActorForwardVector();
	AddMovementInput(Direction, Value);
}

void AXBaseCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = GetActorRightVector();
	AddMovementInput(Direction, Value);
}

void AXBaseCharacter::StartUseHand()
{
	IsUsingHands = true;
}

void AXBaseCharacter::StopUseHand()
{
	IsUsingHands = false;
}

void AXBaseCharacter::StartJump()
{
	IsJumping = true;
	this->Jump();
}

void AXBaseCharacter::StopJump()
{
	IsJumping = true;
}

float AXBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (DamageCauser && DamageAmount > 0)
	{
		Health -= DamageAmount;
		if (Health <= 0)
		{
			Health = 0;
			Kill();
		}
		return DamageAmount;
	}
	return 0.f;
}

void AXBaseCharacter::InflictDamage(float DamageAmount, const FHitResult & Hit)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
	FDamageEvent DamageEvent(ValidDamageTypeClass);
	this->TakeDamage(DamageAmount, DamageEvent, PlayerController, this);
}

float AXBaseCharacter::HealDamage(float HealAmount)
{
	if (HealAmount > 0)
	{
		this->Health += HealAmount;
		return HealAmount;
	}
	return 0.f;
}

void AXBaseCharacter::UseItem(AXItem * Item)
{
	if (Item)
	{
		Item->OnUse(this);
	}
}

void AXBaseCharacter::PickUpItem(AXItem * Item)
{
	if (Item)
	{
		Item->SetActorHiddenInGame(true);
		Item->SetActorEnableCollision(false);
		if (Item->IsStackable())
		{
			for(AXItem * BItem : this->Backpack)
			{
				if (BItem->GetClass() == Item->GetClass())
				{
					BItem->AddToStack(Item->GetStackSize());
					Item->Destroy();
					break;
				}
			}
		}
		this->Backpack.Add(Item);
	}
}

void AXBaseCharacter::DropItem(AXItem * Item, int Amount)
{
	if (Item)
	{
		bool exist = false;
		for (AXItem * BItem : Backpack)
		{
			if (BItem == Item) exist = true;
		}
		if (exist)
		{
			FRotator Rotation = GetActorRotation();
			FVector Location = GetActorLocation() + Rotation.RotateVector(DropOffset);
			

			if (Item->IsStackable())
			{
				if (Amount <= 0)
				{
					Amount = 1;
				}
				if (Item->GetStackSize() > Amount)
				{
					UWorld * World = GetWorld();
					FActorSpawnParameters SpawnParams;
					if (World)
					{
						AXItem * NItem = World->SpawnActor<AXItem>(Item->GetClass(), Location, Rotation, SpawnParams);
						NItem->AddToStack(-NItem->GetStackSize());
						NItem->AddToStack(Amount);
						Item->AddToStack(-Amount);
						return;
					}
					//TODO::
				}
			}
			Item->SetActorLocation(Location);
			Item->SetActorRotation(Rotation);
			Item->SetActorHiddenInGame(false);
			Item->SetActorEnableCollision(true);
			Backpack.Remove(Item);
		}
	}
}

void AXBaseCharacter::EquipTwoHandWeapon(AXTwoHandWeapon * Weapon)
{
	UWorld* World = GetWorld();
	if (World)
	{
		//Parametry dodawania postaci do gry
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		if (Weapon)
		{
			this->UnequipWeapon();
			this->RightHandWeapon = Weapon;
			this->RightHandWeapon->SetActorHiddenInGame(false);
			this->RightHandWeapon->SetActorEnableCollision(true);
			this->RightHandWeaponClass = Weapon->StaticClass();
		}
		else if (RightHandWeaponClass)
		{
			AXWeapon * NewWeapon = World->SpawnActor<AXWeapon>(this->RightHandWeaponClass, SpawnParams);
			this->RightHandWeapon = Cast<AXTwoHandWeapon>(NewWeapon);
		}
		else if (LeftHandWeaponClass)
		{
			this->UnequipWeapon();
			AXWeapon * NewWeapon = World->SpawnActor<AXWeapon>(this->LeftHandWeaponClass, SpawnParams);
			this->RightHandWeapon = Cast<AXTwoHandWeapon>(NewWeapon);
		}
		if (this->RightHandWeapon)
		{
			this->LeftHandWeapon = this->RightHandWeapon;
			this->LeftHandWeaponClass = this->RightHandWeaponClass;
			//Przytwierdzenie do postaci
			FAttachmentTransformRules ARules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
			this->RightHandWeapon->AttachToComponent(GetMesh(), ARules, TEXT("RightHandWeaponSocket"));
			
		}
	}
}

void AXBaseCharacter::EquipOneHandWeapon(AXOneHandWeapon * MainWeapon, AXOneHandWeapon * OffWeapon)
{
	UWorld* World = GetWorld();
	if (World)
	{
		//Parametry dodawania postaci do gry
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		if (MainWeapon)
		{
			RightHandWeapon = MainWeapon;
			this->RightHandWeapon->SetActorHiddenInGame(false);
			this->RightHandWeapon->SetActorEnableCollision(true);
			this->RightHandWeaponClass = MainWeapon->StaticClass();
		}
		else if(RightHandWeaponClass)
		{
			this->UnequipWeapon();
			AXWeapon * NewWeapon = World->SpawnActor<AXWeapon>(this->RightHandWeaponClass, SpawnParams);
			this->RightHandWeapon = Cast<AXOneHandWeapon>(NewWeapon);
		}
		if (OffWeapon)
		{
			LeftHandWeapon = OffWeapon;
			this->LeftHandWeapon->SetActorHiddenInGame(false);
			this->LeftHandWeapon->SetActorEnableCollision(true);
			this->LeftHandWeaponClass = OffWeapon->StaticClass();
		}
		else if (LeftHandWeaponClass)
		{
			AXWeapon * NewWeapon = World->SpawnActor<AXWeapon>(this->LeftHandWeaponClass, SpawnParams);
			this->LeftHandWeapon = Cast<AXOneHandWeapon>(NewWeapon);
		}
		if (RightHandWeapon)
		{
			AXOneHandWeapon * RW = Cast<AXOneHandWeapon>(RightHandWeapon);
			if (RW)
			{
				RW->SetIsRightHand(true);
			}
			RightHandWeapon->SetOwner(this);
			//Przytwierdzenie do postaci
			FAttachmentTransformRules ARules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
			
			RightHandWeapon->AttachToComponent(GetMesh(), ARules, TEXT("RightHandWeaponSocket"));
			//AttachRootComponentTo(GetMesh(), TEXT("RightHandWeaponSocket"), EAttachLocation::SnapToTarget, true);
		}
		if (LeftHandWeapon)
		{
			AXOneHandWeapon * LW = Cast<AXOneHandWeapon>(LeftHandWeapon);
			if (LW)
			{
				LW->SetIsRightHand(false);
			}
			LeftHandWeapon->SetOwner(this);
			//Przytwierdzenie do postaci
			FAttachmentTransformRules ARules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
			LeftHandWeapon->AttachToComponent(GetMesh(), ARules, TEXT("LeftHandWeaponSocket"));
			//LeftHandWeapon->AttachRootComponentTo(GetMesh(), TEXT("LeftHandWeaponSocket"), EAttachLocation::SnapToTarget, true);
		}
	}
}

void AXBaseCharacter::UnequipWeapon()
{
	if (RightHandWeapon)
	{
		RightHandWeapon->DetachRootComponentFromParent();
		RightHandWeapon->SetActorHiddenInGame(true);
		RightHandWeapon->SetActorEnableCollision(false);
		if (RightHandWeapon == LeftHandWeapon)
		{
			LeftHandWeapon = nullptr;
		}
		RightHandWeapon = nullptr;
	}
	if (LeftHandWeapon)
	{
		LeftHandWeapon->DetachRootComponentFromParent();
		LeftHandWeapon->SetActorHiddenInGame(true);
		LeftHandWeapon->SetActorEnableCollision(false);
	}
}

float AXBaseCharacter::GetHealth()
{
	return Health;
}

void AXBaseCharacter::Kill()
{
	/*if (this->Weapon)
		Weapon->Destroy();*/
	Destroy();
}

void AXBaseCharacter::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AXSpace * Space = Cast<AXSpace>(OtherActor);
	if (Space)
	{
		if (Space->GetOwner() != this)
		{
			InflictDamage(Space->GetDamage(), SweepResult);
			Space->OnCollision(this, SweepResult);
		}
	}
}

TArray<AXItem*> AXBaseCharacter::GetBackpack()
{
	return Backpack;
}



