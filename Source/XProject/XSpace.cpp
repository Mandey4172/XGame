// Fill out your copyright notice in the Description page of Project Settings.

#include "XSpace.h"


// Sets default values
AXSpace::AXSpace()
{
	// Czy character ma wywowylac metode Tick()
	PrimaryActorTick.bCanEverTick = true;
	
	/*RootComponent = GetCollisionComponent();

	*/
	//
	Damage = 10;
	// Zniszcz po 
	InitialLifeSpan = 10.0f;
}

// Called when the game starts or when spawned
void AXSpace::BeginPlay()
{
	Super::BeginPlay();
	
}


void AXSpace::Tick(float DeltaTime)
{
}

float AXSpace::GetDamage()
{
	return Damage;
}

void AXSpace::OnCollision(AActor * OtherActor, const FHitResult & SweepResult)
{

}

USphereComponent * AXSpace::GetCollisionComponent()
{
	return nullptr;
}

