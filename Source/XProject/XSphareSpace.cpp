// Fill out your copyright notice in the Description page of Project Settings.

#include "XSphareSpace.h"

AXSphareSpace::AXSphareSpace()
{
	// Uzywaj kuli do reprezentacji kolizji
	SphareCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphareCollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	// Promien kuli
	SphareCollisionComponent->InitSphereRadius(1.0f);
	// Ustawianie glownego komponentu jako component kuli

	RootComponent = SphareCollisionComponent;

	RadiusMinimum = 0.f;
	RadiusMaximum = 100.f;
	RadiusDelta = 0.f;
}

void AXSphareSpace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	* Change size if needed;
	*/
	if (RadiusDelta > 0.f)
	{
		float NextSize = SphareCollisionComponent->GetScaledSphereRadius() + (DeltaTime * RadiusDelta);
		if ((NextSize > 0.f) && (NextSize >= RadiusMinimum) && (NextSize <= RadiusMaximum))
		{
			SphareCollisionComponent->SetSphereRadius(NextSize);
		}
	}
}

UShapeComponent * AXSphareSpace::GetCollisionComponent()
{
	UShapeComponent * CollisionComponent = Cast<UShapeComponent>(SphareCollisionComponent);
	return CollisionComponent;
}

void AXSphareSpace::BeginPlay()
{
	Super::BeginPlay();
}

void AXSphareSpace::SetRadiusDelta(float Radius)
{
	RadiusDelta = Radius;
}

float AXSphareSpace::GetRadiusDelta()
{
	return RadiusDelta;
}

void AXSphareSpace::SetRadiusMinimum(float Minimum)
{
	if (Minimum < 0)
	{
		Minimum *= -1;
	}
	RadiusMinimum = Minimum;
}

float AXSphareSpace::GetRadiusMinimum()
{
	return RadiusMinimum;
}

void AXSphareSpace::SetRadiusMaximum(float Maximum)
{
	if (Maximum < 0)
	{
		Maximum *= -1;
	}
	if (Maximum < RadiusMinimum)
		RadiusMaximum = RadiusMinimum;
	else
		RadiusMaximum = Maximum;
}

float AXSphareSpace::GetRadiusMaximum()
{
	return RadiusMaximum;
}

