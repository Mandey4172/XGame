// Fill out your copyright notice in the Description page of Project Settings.

#include "XCapsuleSpace.h"

AXCapsuleSpace::AXCapsuleSpace()
{
	// Uzywaj kuli do reprezentacji kolizji
	CapsuleCollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SphereComponent"));
	CapsuleCollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	// Promien kuli
	CapsuleCollisionComponent->InitCapsuleSize(10,10);
	// Ustawianie glownego komponentu jako component kuli
	RootComponent = CapsuleCollisionComponent;

	RadiusDelta = 0.f;
	RadiusMinimum = 0.f;
	RadiusMaximum = 100.f;

	HeightDelta = 0.f;
	HeightMinimum = 0.f;
	HeightMaximum = 100.f;
}

void AXCapsuleSpace::Tick(float DeltaTime)
{
	/*if (SpaceSizeDelta.X > 0.f)
	{
		FVector NextSize = CapsuleCollisionComponent->GetCollisionShape()->
		NextSize.X += DeltaTime * this->SpaceSizeDelta.X;
		if (NextSize.X >= SpaceSizeMinimum.X)
		{
			NextSize.X = SpaceSizeMinimum.X;
		}
		else if (NextSize.X <= SpaceSizeMaximum.X)
		{
			NextSize.X = SpaceSizeMaximum.X;
		}
		CapsuleCollisionComponent->SetCapsuleSize(NextSize);
	}
	if (SpaceSizeDelta.Y > 0.f)
	{
		FVector NextSize = CapsuleCollisionComponent->GetScaledCapsuleSize();
		NextSize.Y += DeltaTime * this->SpaceSizeDelta.Y;
		if (NextSize.Y >= SpaceSizeMinimum.Y)
		{
			NextSize.Y = SpaceSizeMinimum.Y;
		}
		else if (NextSize.Y <= SpaceSizeMaximum.Y)
		{
			NextSize.Y = SpaceSizeMaximum.Y;
		}
		CapsuleCollisionComponent->SetCapsuleSize(NextSize);
	}
	if (SpaceSizeDelta.Z > 0.f)
	{
		FVector NextSize = CapsuleCollisionComponent->GetScaledCapsuleSize();
		NextSize.Z += DeltaTime * this->SpaceSizeDelta.Z;
		if (NextSize.Z >= SpaceSizeMinimum.Z)
		{
			NextSize.Z = SpaceSizeMinimum.Z;
		}
		else if (NextSize.X <= SpaceSizeMaximum.X)
		{
			NextSize.Z = SpaceSizeMaximum.Z;
		}
		CapsuleCollisionComponent->SetCapsuleSize(NextSize);
	}*/
}

void AXCapsuleSpace::SetRadiusDelta(float Radius)
{
	if (Radius < 0) Radius = 0.f;
	RadiusDelta = Radius;
}

float AXCapsuleSpace::GetRadiusDelta()
{
	return RadiusDelta;;
}

void AXCapsuleSpace::SetRadiusMinimum(float Minimum)
{
	if (Minimum < 0) Minimum = 0.f;
	RadiusMinimum = Minimum;
}

float AXCapsuleSpace::GetRadiusMinimum()
{
	return RadiusMinimum;
}

void AXCapsuleSpace::SetRadiusMaximum(float Maximum)
{
	if (Maximum < RadiusMinimum) Maximum = RadiusMinimum;
	RadiusMaximum = Maximum;
}

float AXCapsuleSpace::GetRadiusMaximum()
{
	return RadiusMaximum;
}

void AXCapsuleSpace::SetHeightDelta(float Height)
{
	if(Height < 0.f) Height = 0.f;
	HeightDelta = Height;
}

float AXCapsuleSpace::GetHeightDelta()
{
	return HeightDelta;
}

void AXCapsuleSpace::SetHeightMinimum(float Minimum)
{
	if (Minimum < 0) Minimum = 0.f;
	HeightMinimum = Minimum;
}

float AXCapsuleSpace::GetHeightMinimum()
{
	return HeightMinimum;
}

void AXCapsuleSpace::SetHeightMaximum(float Maximum)
{
	if (Maximum < HeightMinimum) Maximum = HeightMinimum;
	HeightMaximum = Maximum;
}

float AXCapsuleSpace::GetHeightMaximum()
{
	return HeightMaximum;
}

USphereComponent * AXCapsuleSpace::GetCollisionComponent()
{
	USphereComponent * CollisionComponent = Cast<USphereComponent>(CapsuleCollisionComponent);
	return CollisionComponent;
}
