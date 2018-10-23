// Fill out your copyright notice in the Description page of Project Settings.

#include "XPlayerCharacter.h"
#include "XPlayerController.h"
#include "XItem.h"

AXPlayerCharacter::AXPlayerCharacter()
{

}

void AXPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AXPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up movement bindings.
	InputComponent->BindAxis("MoveForward", this, &AXPlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AXPlayerCharacter::MoveRight);
	// Set up "look" bindings.
	InputComponent->BindAxis("Turn", this, &AXPlayerCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AXPlayerCharacter::AddControllerPitchInput);
	// Set up jump bindings
	InputComponent->BindAction("JumpInput", IE_Pressed, this, &AXPlayerCharacter::StartJump);
	InputComponent->BindAction("JumpInput", IE_Released, this, &AXPlayerCharacter::StopJump);
	// Set up run bindings
	InputComponent->BindAction("RunInput", IE_Pressed, this, &AXPlayerCharacter::StartRun);
	InputComponent->BindAction("RunInput", IE_Released, this, &AXPlayerCharacter::StopRun);
	// Use hand input bindings.
	InputComponent->BindAction("UseLHandInput", IE_Pressed, this, &AXPlayerCharacter::StartUseHand);
	InputComponent->BindAction("UseLHandInput", IE_Released, this, &AXPlayerCharacter::StopUseHand);
	// Pick up input bindings.
	InputComponent->BindAction("PickUpInput", IE_Pressed, this, &AXPlayerCharacter::PickUpItemInput);
	// Pick up input bindings.
	InputComponent->BindAction("DropInput", IE_Pressed, this, &AXPlayerCharacter::DropItemInput);
	//
	//InputComponent->BindAction("TestInput", IE_Pressed, this, &AXPlayerController::TestInput);
}

void AXPlayerCharacter::PickUpItemInput()
{
	AXPlayerController * Controller = Cast<AXPlayerController>(GetController());
	if (Controller)
	{
		AXItem * Item = Controller->GetSelectedItem();
		if (Item) PickUpItem(Item);
	}
}

void AXPlayerCharacter::DropItemInput()
{
}
