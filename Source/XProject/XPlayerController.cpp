// Fill out your copyright notice in the Description page of Project Settings.


#include "XPlayerController.h"
#include "XBaseCharacter.h"
#include "XCamera.h"
#include "XOneHandWeapon.h"
#include "XTwoHandWeapon.h"
#include "XItem.h"

AXPlayerController::AXPlayerController()
{
	this->PrimaryActorTick.bCanEverTick = true;
	PickUpRange = 600.f;
}

void AXPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWorld * World = GetWorld();
	APawn * Pawn = GetPawn();
	if (CameraActor && World)
	{
		const FName TraceTag("XTraceTag");

		//World->DebugDrawTraceTag = TraceTag;

		FCollisionQueryParams ColParams;
		ColParams.bTraceComplex = true;
		ColParams.bTraceAsyncScene = true;
		ColParams.bReturnPhysicalMaterial = false;
		ColParams.TraceTag = TraceTag;

		FRotator Rotation;
		FVector Start;
		CameraActor->GetActorEyesViewPoint(Start, Rotation);
		FVector MaxRange = FVector(PickUpRange, 0.f, 0.f);
		FVector End = CameraActor->GetActorLocation() + CameraActor->GetActorRotation().RotateVector(MaxRange);
		FHitResult HitOut;
		World->LineTraceSingleByChannel(HitOut, Start, End, Pawn->GetRootComponent()->GetCollisionObjectType(), ColParams);
		AActor * Actor = HitOut.Actor.Get();
		AXItem * Item = Cast<AXItem>(Actor);
		if (Item && HitOut.Distance < PickUpRange)
		{
			ItemColdown = 2.5f;
			ItemToPick = Item;
		}
		/*this->CursorLocation = CameraActor->GetActorLocation() + CameraActor->GetActorRotation().RotateVector(MaxRange);
		if (HitOut.bBlockingHit)
		{
			this->CursorLocation = HitOut.Location;
		}*/
		//AXBaseCharacter * Character = Cast<AXBaseCharacter>(Pawn);
		//if (Character)
		//{
		//	FVector CharacterStart = Character->GetActorLocation();
		//	FVector CharacterEnd = CameraActor->GetActorLocation() + CameraActor->GetActorRotation().RotateVector(MaxRange);
		//	if (Actor)
		//	{
		//		CharacterEnd = HitOut.Location;
		//	}
		//	FVector Result = CharacterEnd - CharacterStart;
		//	FRotator ARot = Character->GetActorRotation();
		//	ARot.Pitch = Result.Rotation().Pitch;
		//	Character->AimPitch = ARot.Pitch;
		//	//Character->SetActorRotation(ARot);
		//}
		
		
		
		//End -= Pawn->GetActorLocation();
		//End.Normalize();
		////R = End.Rotation();
		//AXBaseCharacter * Character = Cast<AXBaseCharacter>(Pawn);
		//if (Character)
		//	Character->AimPitch = End.Rotation().Pitch;
		//World->LineTraceSingleByChannel(Start, End,Pawn->GetRootComponent()->GetCollisionObjectType());
	}
	if (ItemColdown > 0.f)
	{
		ItemColdown -= DeltaTime;
		if (ItemColdown <= 0.f)
			ItemToPick = nullptr;
	}
}

AXCamera * AXPlayerController::SetupCamera(AActor * NOwner)
{
	UWorld * World = GetWorld();
	if (!CameraClass)
	{
		CameraClass = AXCamera::StaticClass();
	}
	if (World)
	{
		FRotator				Rotation = FRotator(0.f);
		FVector					Location = FVector(0.f, 0.f, 100.f);
		FActorSpawnParameters	SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		if (NOwner)
		{
			SpawnParams.Owner = NOwner;
		}
		this->CameraActor = World->SpawnActor<AXCamera>(CameraClass->GetDefaultObject()->GetClass(), Location, Rotation, SpawnParams);
	}
	SetViewTarget(CameraActor);

	return CameraActor;
}

AXCamera * AXPlayerController::GetCamera()
{
	return CameraActor;
}

AXItem * AXPlayerController::GetItemToPick()
{
	return ItemToPick;
}

void AXPlayerController::BeginPlay()
{
	
}

void AXPlayerController::SetupInputComponent()
{

	Super::SetupInputComponent();

	// Set up movement bindings.
	InputComponent->BindAxis("MoveForward", this, &AXPlayerController::MoveForwardInput);
	InputComponent->BindAxis("MoveRight", this, &AXPlayerController::MoveRightInput);
	// Set up "look" bindings.
	InputComponent->BindAxis("Turn", this, &AXPlayerController::AddYawInput);
	InputComponent->BindAxis("LookUp", this, &AXPlayerController::AddPitchInput);
	// Set up jump bindings
	InputComponent->BindAction("JumpInput", IE_Pressed, this, &AXPlayerController::StartJumpInput);
	InputComponent->BindAction("JumpInput", IE_Released, this, &AXPlayerController::StopJumpInput);
	// Use hand input bindings.
	InputComponent->BindAction("UseLHandInput", IE_Pressed, this, &AXPlayerController::StartUseHandInput);
	InputComponent->BindAction("UseLHandInput", IE_Released, this, &AXPlayerController::StopUseHandInput);
	// Pick up input bindings.
	InputComponent->BindAction("PickUpInput", IE_Pressed, this, &AXPlayerController::PickUpItemInput);
	// Pick up input bindings.
	InputComponent->BindAction("DropInput", IE_Pressed, this, &AXPlayerController::DropItemInput);
	//
	InputComponent->BindAction("TestInput", IE_Pressed, this, &AXPlayerController::TestInput);
}

void AXPlayerController::MoveForwardInput(float Value)
{
	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
	if (Character)
		Character->MoveForward(Value);
}

void AXPlayerController::MoveRightInput(float Value)
{
	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
	if (Character)
		Character->MoveRight(Value);
}

void AXPlayerController::AddYawInput(float Value)
{
	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
	if (CameraActor && Character)
	{
		CameraActor->AddYaw(Value);
		FRotator Rotation = Character->GetActorRotation();
		Rotation.Yaw += Value;
		Character->SetActorRotation(Rotation);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Rotation.ToString() );
	}
}

void AXPlayerController::AddPitchInput(float Value)
{
	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
	if (CameraActor && Character)
	{
		CameraActor->AddPitch(Value);
		Character->AimPitch += Value;
	}
}

void AXPlayerController::StartUseHandInput()
{
	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
	if(Character)
		Character->StartUseHand();
}

void AXPlayerController::StopUseHandInput()
{
	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
	if (Character)
		Character->StopUseHand();
}

void AXPlayerController::StartJumpInput()
{
	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
	if (Character)
		Character->StartJump();
}

void AXPlayerController::StopJumpInput()
{
	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
	if (Character)
		Character->StopJump();
}

void AXPlayerController::PickUpItemInput()
{
	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
	if (Character && ItemToPick)
	{
		Character->PickUpItem(ItemToPick);
		ItemToPick = nullptr;
	}
}

void AXPlayerController::DropItemInput()
{
	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
	if (Character && Character->GetBackpack().Num() > 0)
	{
		Character->DropItem(Character->GetBackpack()[0], 1);
	}
}

void AXPlayerController::TestInput()
{
	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
	if (Character)
	{
		TArray<AXItem *> Items = Character->GetBackpack();
		if (Items.Num())
		{
			AXOneHandWeapon * MainWeapon = nullptr;
			AXOneHandWeapon * OffWeapon = nullptr;

			for (AXItem * Item : Items)
			{
				AXTwoHandWeapon * TwoHand = Cast<AXTwoHandWeapon>(Item);
				if (TwoHand)
				{
					Character->EquipTwoHandWeapon(TwoHand);
					return;
				}
				if(!MainWeapon)
					MainWeapon = Cast<AXOneHandWeapon>(Item);
				else if(!OffWeapon)
					OffWeapon = Cast<AXOneHandWeapon>(Item);
			}
			if (MainWeapon)
			{
				Character->EquipOneHandWeapon(MainWeapon, OffWeapon);
			}
		}
	}
}
