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
	IsJumping = false;

	IsUsingRightHand = false;
	IsUsingLeftHand = false;

	// Czy character ma wywowylac metode Tick()
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&AXBaseCharacter::BeginOverlap);
	
	MaxHealth = 100.f;
	Health = MaxHealth;

	RunMultiply = 2.f;

	DropOffset = FVector(150.f,0.f,0.f);
}

// Called when the game starts or when spawned
void AXBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;

	AXPlayerController * PC = Cast<AXPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PC)
	{
		PC->SetupCamera(this);
	}
	UWorld* World = GetWorld();
	if (World)
	{
		//Parametry aktora podczas dodawania 
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;	
		bool IsOneHand = true;
		AXWeapon * RWeapon = World->SpawnActor<AXWeapon>(RightHandWeaponClass, SpawnParams);
		AXWeapon * LWeapon = World->SpawnActor<AXWeapon>(LeftHandWeaponClass, SpawnParams);

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

void AXBaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnequipWeapon();
	while (Backpack.Num() > 0)
	{
		AXItem * Item = Backpack[0];
		DropItem(Item);
	}
	/*if (Backpack.Num() > 0)
	{
		
		for (AXItem * Item : Backpack)
		{
			DropItem(Item);
		}
	}*/
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AXBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RightHandWeapon && LeftHandWeapon && (LeftHandWeapon == RightHandWeapon)
		&& IsUsingRightHand  && IsUsingLeftHand )
	{
		RightHandWeapon->Use(this);
	}
	else
	{
		if (RightHandWeapon && IsUsingRightHand)
		{
			RightHandWeapon->Use(this);
		}
		if (LeftHandWeapon && IsUsingLeftHand)
		{
			LeftHandWeapon->Use(this);
		}
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
	IsUsingRightHand = true;
	IsUsingLeftHand = true;
}

void AXBaseCharacter::StopUseHand()
{
	IsUsingRightHand = false;
	IsUsingLeftHand = false;
}

void AXBaseCharacter::StartJump()
{
	IsJumping = true;
	Jump();
}

void AXBaseCharacter::StopJump()
{
	IsJumping = true;
}

void AXBaseCharacter::StartRun()
{
	GetCharacterMovement()->MaxWalkSpeed *= RunMultiply;
}

void AXBaseCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed /= RunMultiply;
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
	TakeDamage(DamageAmount, DamageEvent, PlayerController, this);
}

float AXBaseCharacter::HealDamage(float HealAmount)
{
	if (HealAmount > 0)
	{
		Health += HealAmount;
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
		Item->CollisionComponent->SetEnableGravity(false);
		if (Item->IsStackable())
		{
			for(AXItem * BabckpackItem : Backpack)
			{
				if (BabckpackItem->GetClass() == Item->GetClass())
				{
					BabckpackItem->AddToStack(Item->GetStackSize());
					Item->Destroy();
					break;
				}
			}
		}
		else
			Backpack.Add(Item);
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
			FRotator Rotation = FRotator::ZeroRotator;
			Rotation.Yaw = GetActorRotation().Yaw;
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
						NItem->AddToStack(Amount);
						Item->AddToStack(Item->GetStackSize() - Amount);
						
						NItem->SetActorLocation(Location);
						NItem->SetActorRotation(Rotation);
						NItem->SetActorHiddenInGame(false);
						NItem->SetActorEnableCollision(true);
						NItem->CollisionComponent->SetEnableGravity(true);
						
						return;
					}
				}
			}
			Item->SetActorLocation(Location);
			Item->SetActorRotation(Rotation);
			Item->SetActorHiddenInGame(false);
			Item->SetActorEnableCollision(true);
			Item->CollisionComponent->SetEnableGravity(true);
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
			UnequipWeapon();
			RightHandWeapon = Weapon;
			RightHandWeaponClass = Weapon->StaticClass();
		}
		else if (RightHandWeaponClass)
		{
			AXWeapon * NewWeapon = World->SpawnActor<AXWeapon>(RightHandWeaponClass, SpawnParams);
			RightHandWeapon = Cast<AXTwoHandWeapon>(NewWeapon);
		}
		else if (LeftHandWeaponClass)
		{
			UnequipWeapon();
			AXWeapon * NewWeapon = World->SpawnActor<AXWeapon>(LeftHandWeaponClass, SpawnParams);
			RightHandWeapon = Cast<AXTwoHandWeapon>(NewWeapon);
		}
		if (RightHandWeapon)
		{
			RightHandWeapon->SetActorHiddenInGame(false);
			RightHandWeapon->SetActorEnableCollision(false);
			RightHandWeapon->CollisionComponent->SetEnableGravity(true);
			LeftHandWeapon = RightHandWeapon;
			LeftHandWeaponClass = RightHandWeaponClass;
			//Przytwierdzenie do postaci
			FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
			RightHandWeapon->AttachToComponent(GetMesh(), AttachmentTransformRules, TEXT("RightHandWeaponSocket"));
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
			RightHandWeaponClass = MainWeapon->StaticClass();
		}
		else if(RightHandWeaponClass)
		{
			UnequipWeapon();
			AXWeapon * NewWeapon = World->SpawnActor<AXWeapon>(RightHandWeaponClass, SpawnParams);
			RightHandWeapon = Cast<AXOneHandWeapon>(NewWeapon);
		}
		if (OffWeapon)
		{
			LeftHandWeapon = OffWeapon;
			LeftHandWeapon->SetActorHiddenInGame(false);
			LeftHandWeapon->SetActorEnableCollision(true);
			LeftHandWeaponClass = OffWeapon->StaticClass();
		}
		else if (LeftHandWeaponClass)
		{
			AXWeapon * NewWeapon = World->SpawnActor<AXWeapon>(LeftHandWeaponClass, SpawnParams);
			LeftHandWeapon = Cast<AXOneHandWeapon>(NewWeapon);
		}
		if (RightHandWeapon)
		{
			RightHandWeapon->SetActorHiddenInGame(false);
			RightHandWeapon->SetActorEnableCollision(false);
			RightHandWeapon->CollisionComponent->SetEnableGravity(true);

			AXOneHandWeapon * RW = Cast<AXOneHandWeapon>(RightHandWeapon);
			if (RW)
			{
				RW->SetIsRightHand(true);
			}
			RightHandWeapon->SetOwner(this);
			//Przytwierdzenie do postaci
			FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
			RightHandWeapon->AttachToComponent(GetMesh(), AttachmentTransformRules, TEXT("RightHandWeaponSocket"));
			//AttachRootComponentTo(GetMesh(), TEXT("RightHandWeaponSocket"), EAttachLocation::SnapToTarget, true);
		}
		if (LeftHandWeapon)
		{
			LeftHandWeapon->SetActorHiddenInGame(false);
			LeftHandWeapon->SetActorEnableCollision(false);
			LeftHandWeapon->CollisionComponent->SetEnableGravity(true);

			AXOneHandWeapon * LW = Cast<AXOneHandWeapon>(LeftHandWeapon);
			if (LW)
			{
				LW->SetIsRightHand(false);
			}
			LeftHandWeapon->SetOwner(this);
			//Przytwierdzenie do postaci
			FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
			LeftHandWeapon->AttachToComponent(GetMesh(), AttachmentTransformRules, TEXT("LeftHandWeaponSocket"));
			//LeftHandWeapon->AttachRootComponentTo(GetMesh(), TEXT("LeftHandWeaponSocket"), EAttachLocation::SnapToTarget, true);
		}
	}
}

void AXBaseCharacter::UnequipWeapon()
{
	FDetachmentTransformRules DRules(EDetachmentRule::KeepWorld, true);
	if (RightHandWeapon)
	{
		RightHandWeapon->DetachFromActor(DRules);
		/*RightHandWeapon->DetachRootComponentFromParent();
		RightHandWeapon->SetActorHiddenInGame(true);
		RightHandWeapon->SetActorEnableCollision(false);*/
		if (RightHandWeapon == LeftHandWeapon)
		{
			LeftHandWeapon = nullptr;
		}
		/*RightHandWeapon->Destroy();*/
		PickUpItem(RightHandWeapon);
		RightHandWeapon = nullptr;
	}
	if (LeftHandWeapon)
	{
		LeftHandWeapon->DetachFromActor(DRules);
		/*LeftHandWeapon->SetActorHiddenInGame(true);
		LeftHandWeapon->SetActorEnableCollision(false);
		LeftHandWeapon->Destroy();*/
		PickUpItem(LeftHandWeapon);
		LeftHandWeapon = nullptr;
	}
}

float AXBaseCharacter::GetHealth()
{
	return Health;
}

void AXBaseCharacter::Kill()
{
	/*if (Weapon)
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

float AXBaseCharacter::GetMaxHealth()
{
	return MaxHealth;
}

void AXBaseCharacter::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
}

AXWeapon * AXBaseCharacter::GetRightHandWeapon()
{
	return RightHandWeapon;
}

AXWeapon * AXBaseCharacter::GetLeftHandWeapon()
{
	return LeftHandWeapon;
}



