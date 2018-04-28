// Fill out your copyright notice in the Description page of Project Settings.

#include "XWeapon.h"

AXWeapon::AXWeapon()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//ActorMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("StaticMeshComponent"));
	//// Prztwierdzenie do glownego komponentu
	//ActorMeshComponent->AttachTo(GetRootComponent());
}

void AXWeapon::Use()
{
	int x = 0;
}
