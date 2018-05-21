// Fill out your copyright notice in the Description page of Project Settings.

#include "XOneHandWeapon.h"
#include "XBaseCharacter.h"

AXOneHandWeapon::AXOneHandWeapon()
{
	RightHand = true;
}

void AXOneHandWeapon::OnUse(AXBaseCharacter * Character)
{

}

void AXOneHandWeapon::SetIsRightHand(bool nRightHand)
{
	RightHand = nRightHand;
}

bool AXOneHandWeapon::IsRightHand()
{
	return RightHand;
}

void AXOneHandWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXOneHandWeapon::BeginPlay()
{
	Super::BeginPlay();
}
