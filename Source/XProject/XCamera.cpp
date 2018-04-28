// Fill out your copyright notice in the Description page of Project Settings.

#include "XCamera.h"

#include <EngineMinimal.h>
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

// Sets default values
AXCamera::AXCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);

	Offset = FVector(-200.f, 0.f, 0.f);
	Pitch = 0.f;
	Yaw = 180.f;

	PitchLimit = 45.f;
	YawLimit = 0.f;
}

// Called when the game starts or when spawned
void AXCamera::BeginPlay()
{
	Super::BeginPlay();

	AActor * Owner = this->GetOwner();
	if (Owner)
	{
		PrimaryActorTick.AddPrerequisite(Owner, Owner->PrimaryActorTick);
		FVector Location;
		FRotator Rotation;
		Owner->GetActorEyesViewPoint(Location, Rotation);

		FRotator CameraRotation(Pitch, Yaw, 0);
		FVector Result = CameraRotation.RotateVector(Offset);
		SetActorLocation(Location + Result);
		SetActorRotation(Rotation);
	}
}

// Called every frame
void AXCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor * Owner = this->GetOwner();
	if (Owner)
	{
		FVector Location;
		FRotator Rotation;
		Owner->GetActorEyesViewPoint(Location,Rotation);

		FRotator CameraRotation(Pitch, Yaw, 0);
		FVector Result = CameraRotation.RotateVector(Offset);
		SetActorLocation(Location + Result);
		SetActorRotation(FRotator(Pitch, Yaw, 0));
	}
}

void AXCamera::AddPitch(float Delta)
{
	Pitch += Delta;
	if (PitchLimit != 0.f)
	{
		if (Pitch > PitchLimit)
		{
			Pitch = PitchLimit;
		}
		else if (Pitch < -PitchLimit)
		{
			Pitch = -PitchLimit;
		}
	}
}

void AXCamera::AddYaw(float Delta)
{
	AActor * Owner = GetOwner();
	float AYaw = 0.f;
	if (Owner)
	{
		AYaw = Owner->GetActorRotation().Yaw;
	}
	Yaw += Delta;
	if (YawLimit != 0.f)
	{
		if (AYaw - Yaw > YawLimit)
		{
			Yaw = AYaw - Yaw;
		}
		else if (AYaw - Yaw < -YawLimit)
		{
			Yaw = -AYaw + Yaw;
		}
	}
}

float AXCamera::GetPitch()
{
	return Pitch;
}

float AXCamera::GetYaw()
{
	return Yaw;
}

//void AXCamera::SetTarget(AActor * NewTarget)
//{
//	this->Target = NewTarget;
//}
//
//AActor * AXCamera::GetTarget()
//{
//	return this->Target;
//}

