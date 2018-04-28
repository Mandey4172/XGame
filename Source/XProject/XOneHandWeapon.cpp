// Fill out your copyright notice in the Description page of Project Settings.

#include "XOneHandWeapon.h"


AXOneHandWeapon::AXOneHandWeapon()
{
	RightHand = true;
}

void AXOneHandWeapon::Use()
{
	int x = 10;
}

void AXOneHandWeapon::SetIsRightHand(bool nRightHand)
{
	RightHand = nRightHand;
}

bool AXOneHandWeapon::IsRightHand()
{
	return RightHand;
}
