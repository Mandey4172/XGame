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

	HalfHeightDelta = 0.f;
	HalfHeightMinimum = 0.f;
	HalfHeightMaximum = 100.f;
}

void AXCapsuleSpace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	* Change size if needed;
	*/
	if (RadiusDelta > 0.f)
	{
		float NextSize = CapsuleCollisionComponent->GetScaledCapsuleRadius() + (DeltaTime * RadiusDelta);
		if ((NextSize > 0.f) && (NextSize >= RadiusMinimum) && (NextSize <= RadiusMaximum))
		{
			CapsuleCollisionComponent->SetCapsuleRadius(NextSize);
		}
	}
	if (HalfHeightDelta > 0.f)
	{
		float NextSize = CapsuleCollisionComponent->GetScaledCapsuleHalfHeight() + (DeltaTime * HalfHeightDelta);
		if ((NextSize > 0.f) && (NextSize >= HalfHeightMinimum) && (NextSize <= HalfHeightMaximum))
		{
			CapsuleCollisionComponent->SetCapsuleHalfHeight(NextSize);
		}
	}
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
	HalfHeightDelta = Height;
}

float AXCapsuleSpace::GetHeightDelta()
{
	return HalfHeightDelta;
}

void AXCapsuleSpace::SetHeightMinimum(float Minimum)
{
	if (Minimum < 0) Minimum = 0.f;
	HalfHeightMinimum = Minimum;
}

float AXCapsuleSpace::GetHeightMinimum()
{
	return HalfHeightMinimum;
}

void AXCapsuleSpace::SetHeightMaximum(float Maximum)
{
	if (Maximum < HalfHeightMinimum) Maximum = HalfHeightMinimum;
	HalfHeightMaximum = Maximum;
}

float AXCapsuleSpace::GetHeightMaximum()
{
	return HalfHeightMaximum;
}

UShapeComponent * AXCapsuleSpace::GetCollisionComponent()
{
	UShapeComponent * CollisionComponent = Cast<UShapeComponent>(CapsuleCollisionComponent);
	return CollisionComponent;
}

void AXCapsuleSpace::BeginPlay()
{
	Super::BeginPlay();
}
