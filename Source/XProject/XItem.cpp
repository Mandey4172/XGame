// Fill out your copyright notice in the Description page of Project Settings.

#include "XItem.h"
#include "XBaseCharacter.h"

// Sets default values
AXItem::AXItem()
{
	// Czy character ma wywowylac metode Tick()
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	// Tworzenie komponentu kuli z kolizja
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// Ustawianie promienia kuli
	USphereComponent * MyCollisionComponent = Cast<USphereComponent>(CollisionComponent);
	MyCollisionComponent->InitSphereRadius(1.0f);
	// Ustanienie glownego komponentu jako komponentu kuli
	RootComponent = CollisionComponent;

	bIsStackable = false;
	StackSize = 1;
	StackMaximalSize = 255;
}

// Called when the game starts or when spawned
void AXItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AXItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Coldown > 0.f)
	{
		Coldown -= DeltaTime;
	}
}

void AXItem::Use(AXBaseCharacter * Character)
{
	if (Coldown <= 0.f)
	{
		OnUse(Character);
		Coldown = OnUseColdown;
	}
}

void AXItem::OnUse(AXBaseCharacter * Character)
{
	
}

bool AXItem::IsStackable()
{
	return bIsStackable;
}

int AXItem::GetStackSize()
{
	return StackSize;
}

int AXItem::GetStackMaximalSize()
{
	return StackMaximalSize;
}

void AXItem::AddToStack(int Val)
{
	this->StackSize += Val;
}
