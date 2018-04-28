// Fill out your copyright notice in the Description page of Project Settings.

#include "XItem.h"
#include "XBaseCharacter.h"

// Sets default values
AXItem::AXItem()
{
	// Czy character ma wywowylac metode Tick()
	PrimaryActorTick.bCanEverTick = false;
	// Tworzenie komponentu kuli z kolizja
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// Ustawianie promienia kuli
	USphereComponent * MyCollisionComponent = Cast<USphereComponent>(CollisionComponent);
	MyCollisionComponent->InitSphereRadius(1.0f);
	// Ustanienie glownego komponentu jako komponentu kuli
	RootComponent = CollisionComponent;

	ActorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	ActorMeshComponent->AttachTo(GetRootComponent());

	bIsStackable = false;
	StackSize = 1;
	StackMaximalSize = 255;
}

// Called when the game starts or when spawned
void AXItem::BeginPlay()
{
	Super::BeginPlay();
	
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
