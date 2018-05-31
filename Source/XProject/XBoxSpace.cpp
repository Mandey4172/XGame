// Fill out your copyright notice in the Description page of Project Settings.

#include "XBoxSpace.h"
#include "Core.h"

AXBoxSpace::AXBoxSpace()
{
	//// Uzywaj kuli do reprezentacji kolizji
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComponent"));
	BoxCollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	// Promien kuli
	BoxCollisionComponent->InitBoxExtent(FVector(1.f,1.f,1.f));
	// Ustawianie glownego komponentu jako component kuli
	RootComponent = BoxCollisionComponent;

	SpaceSizeDelta = FVector(0.f,0.f,0.f);
	SpaceSizeMinimum = FVector(0.f,0.f,0.f);
	SpaceSizeMaximum = FVector(1000.f,1000.f,1000.f);
}

void AXBoxSpace::Tick(float DeltaTime)
{
	if (SpaceSizeDelta.X > 0.f)
	{
		FVector NextSize = BoxCollisionComponent->GetScaledBoxExtent();
		NextSize.X += DeltaTime * SpaceSizeDelta.X;
		if (NextSize.X >= SpaceSizeMinimum.X)
		{
			NextSize.X = SpaceSizeMinimum.X;
		}
		else if (NextSize.X <= SpaceSizeMaximum.X)
		{
			NextSize.X = SpaceSizeMaximum.X;
		}
		BoxCollisionComponent->SetBoxExtent(NextSize);
	}
	if (SpaceSizeDelta.Y > 0.f)
	{
		FVector NextSize = BoxCollisionComponent->GetScaledBoxExtent();
		NextSize.Y += DeltaTime * SpaceSizeDelta.Y;
		if (NextSize.Y >= SpaceSizeMinimum.Y)
		{
			NextSize.Y = SpaceSizeMinimum.Y;
		}
		else if (NextSize.Y <= SpaceSizeMaximum.Y)
		{
			NextSize.Y = SpaceSizeMaximum.Y;
		}
		BoxCollisionComponent->SetBoxExtent(NextSize);
	}
	if (SpaceSizeDelta.Z > 0.f)
	{
		FVector NextSize = BoxCollisionComponent->GetScaledBoxExtent();
		NextSize.Z += DeltaTime * SpaceSizeDelta.Z;
		if (NextSize.Z >= SpaceSizeMinimum.Z)
		{
			NextSize.Z = SpaceSizeMinimum.Z;
		}
		else if (NextSize.X <= SpaceSizeMaximum.X)
		{
			NextSize.Z = SpaceSizeMaximum.Z;
		}
		BoxCollisionComponent->SetBoxExtent(NextSize);
	}
}

USphereComponent * AXBoxSpace::GetCollisionComponent()
{
	USphereComponent * CollisionComponent = Cast<USphereComponent>(BoxCollisionComponent);
	return CollisionComponent;
}

void AXBoxSpace::SetSpaceSizeDelta(FVector SpaceSize)
{
	if (SpaceSize.X < 0) SpaceSize.X *= -1;
	if (SpaceSize.Y < 0) SpaceSize.Y *= -1;
	if (SpaceSize.Z < 0) SpaceSize.Z *= -1;
	SpaceSizeDelta = SpaceSize;
}

FVector AXBoxSpace::GetSpaceSizeDelta()
{
	return SpaceSizeDelta;
}

void AXBoxSpace::SetSpaceSizeMinimum(FVector Minimum)
{
	if (Minimum.X < 0) Minimum.X = 0.f;
	if (Minimum.Y < 0) Minimum.Y = 0.f;
	if (Minimum.Z < 0) Minimum.Z = 0.f;
	SpaceSizeMinimum = Minimum;
}

FVector AXBoxSpace::GetSpaceSizeMinimum()
{
	return SpaceSizeMinimum;
}

void AXBoxSpace::SetSpaceSizeMaximum(FVector Maximum)
{
	if (Maximum.X < SpaceSizeMinimum.X) Maximum.X = SpaceSizeMinimum.X;
	if (Maximum.Y < SpaceSizeMinimum.Y) Maximum.Y = SpaceSizeMinimum.Y;
	if (Maximum.Z < SpaceSizeMinimum.Z) Maximum.Z = SpaceSizeMinimum.Z;
	SpaceSizeMaximum = Maximum;
}

FVector AXBoxSpace::GetSpaceSizeMaximum()
{
	return SpaceSizeMaximum;
}
