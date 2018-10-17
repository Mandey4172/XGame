// Fill out your copyright notice in the Description page of Project Settings.


#include "XPlayerController.h"
#include "XBaseCharacter.h"
#include "XCamera.h"
#include "XOneHandWeapon.h"
#include "XTwoHandWeapon.h"
#include "XItem.h"

AXPlayerController::AXPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	PickUpRange = 600.f;
}

void AXPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWorld * World = GetWorld();
	APawn * Pawn = GetPawn();
	if (CameraActor && World && Pawn)
	{
		const FName TraceTag("XCursorTraceTag");

		//Create a trace line to find interactions
		FCollisionQueryParams ColisionParams;
		ColisionParams.bTraceComplex = true;
		ColisionParams.bTraceAsyncScene = true;
		ColisionParams.bReturnPhysicalMaterial = false;
		ColisionParams.TraceTag = TraceTag;

		FRotator Rotation;
		FVector Start, End;
		FVector MaxRange = FVector(PickUpRange, 0.f, 0.f);
		FHitResult HitOut;

		CameraActor->GetActorEyesViewPoint(Start, Rotation);
		End = CameraActor->GetActorLocation() + CameraActor->GetActorRotation().RotateVector(MaxRange);
		
		World->LineTraceSingleByChannel(HitOut, Start, End, ECollisionChannel::ECC_WorldDynamic, ColisionParams);
		AXItem * Item = Cast<AXItem>(HitOut.Actor.Get());
		//If hit actor is Item and it's in distance 
		if (Item && FVector::Distance(GetPawn()->GetActorLocation(), Item->GetActorLocation()) <= PickUpRange)
		{
			SelectedItem = Item;
		}
	}
	//Clear item to pick up when you leave pick up distance
	if (Pawn && SelectedItem)
	{
		if(FVector::Distance(Pawn->GetActorLocation(), SelectedItem->GetActorLocation()) > PickUpRange)
			SelectedItem = nullptr;
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
		CameraActor = World->SpawnActor<AXCamera>(CameraClass->GetDefaultObject()->GetClass(), Location, Rotation, SpawnParams);
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
	return SelectedItem;
}

bool AXPlayerController::GetBlockInput()
{
	return BlockPawnInput;
}

void AXPlayerController::SetBlockInput(bool NewBlockInput)
{
	BlockPawnInput = NewBlockInput;
}

AXItem * AXPlayerController::GetSelectedItem()
{
	return SelectedItem;
}

void AXPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AXPlayerController::SetupInputComponent()
{

	Super::SetupInputComponent();

	//// Set up movement bindings.
	//InputComponent->BindAxis("MoveForward", this, &AXPlayerController::MoveForwardInput);
	//InputComponent->BindAxis("MoveRight", this, &AXPlayerController::MoveRightInput);
	//// Set up "look" bindings.
	//InputComponent->BindAxis("Turn", this, &AXPlayerController::AddYawInput);
	//InputComponent->BindAxis("LookUp", this, &AXPlayerController::AddPitchInput);
	//// Set up jump bindings
	//InputComponent->BindAction("JumpInput", IE_Pressed, this, &AXPlayerController::StartJumpInput);
	//InputComponent->BindAction("JumpInput", IE_Released, this, &AXPlayerController::StopJumpInput);
	//// Use hand input bindings.
	//InputComponent->BindAction("UseLHandInput", IE_Pressed, this, &AXPlayerController::StartUseHandInput);
	//InputComponent->BindAction("UseLHandInput", IE_Released, this, &AXPlayerController::StopUseHandInput);
	//// Pick up input bindings.
	//InputComponent->BindAction("PickUpInput", IE_Pressed, this, &AXPlayerController::PickUpItemInput);
	//// Pick up input bindings.
	//InputComponent->BindAction("DropInput", IE_Pressed, this, &AXPlayerController::DropItemInput);
	////
	//InputComponent->BindAction("TestInput", IE_Pressed, this, &AXPlayerController::TestInput);
}

//void AXPlayerController::MoveForwardInput(float Value)
//{
//	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
//	if (Character)
//		Character->MoveForward(Value);
//}
//
//void AXPlayerController::MoveRightInput(float Value)
//{
//	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
//	if (Character)
//		Character->MoveRight(Value);
//}

//void AXPlayerController::AddYawInput(float Value)
//{
//	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
//	if (CameraActor && Character)
//	{
//		CameraActor->AddYaw(Value);
//		FRotator Rotation = Character->GetActorRotation();
//		Rotation.Yaw += Value;
//		Character->SetActorRotation(Rotation);
//	}
//}
//
//void AXPlayerController::AddPitchInput(float Value)
//{
//	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
//	if (CameraActor && Character)
//	{
//		CameraActor->AddPitch(Value);
//		Character->AimPitch += Value;
//	}
//}
//
//void AXPlayerController::StartUseHandInput()
//{
//	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
//	if(Character)
//		Character->StartUseHand();
//}
//
//void AXPlayerController::StopUseHandInput()
//{
//	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
//	if (Character)
//		Character->StopUseHand();
//}
//
//void AXPlayerController::StartJumpInput()
//{
//	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
//	if (Character)
//		Character->StartJump();
//}
//
//void AXPlayerController::StopJumpInput()
//{
//	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
//	if (Character)
//		Character->StopJump();
//}
//
//void AXPlayerController::PickUpItemInput()
//{
//	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
//	if (Character && SelectedItem)
//	{
//		Character->PickUpItem(SelectedItem);
//		SelectedItem = nullptr;
//	}
//}
//
//void AXPlayerController::DropItemInput()
//{
//	AXBaseCharacter * Character = Cast<AXBaseCharacter>(GetPawn());
//	if (Character && Character->GetBackpack().Num() > 0)
//	{
//		Character->DropItem(Character->GetBackpack()[0], 1);
//	}
//}

void AXPlayerController::TestInput()
{

}
