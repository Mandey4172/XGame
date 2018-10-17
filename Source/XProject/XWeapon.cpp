// Fill out your copyright notice in the Description page of Project Settings.

#include "XWeapon.h"
#include "XBaseCharacter.h"

AXWeapon::AXWeapon()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ActorMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("StaticMeshComponent"));
	ActorMeshComponent->SetupAttachment(GetRootComponent());
	//ActorMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("StaticMeshComponent"));
	//// Prztwierdzenie do glownego komponentu
	//ActorMeshComponent->AttachTo(GetRootComponent());
}

void AXWeapon::OnUse(AXBaseCharacter * Character)
{
	
}

void AXWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXWeapon::BeginPlay()
{
	Super::BeginPlay();
}
