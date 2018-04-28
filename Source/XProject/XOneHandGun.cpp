// Fill out your copyright notice in the Description page of Project Settings.

#include "XOneHandGun.h"
#include "XProjectile.h"
#include "XBaseCharacter.h"
#include "XPlayerController.h"

AXOneHandGun::AXOneHandGun()
{
	Offset = FVector(50.f, 5.f, 0.f);
}

void AXOneHandGun::Use()
{
	AXBaseCharacter * Owner = Cast<AXBaseCharacter>(GetOwner());
	if (Owner)
	{
		AXPlayerController * PlayerController = Cast<AXPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (PlayerController)
		{
			FVector Location;
			FRotator Rotation;
			FActorSpawnParameters SpawnParams;

			Owner->GetActorEyesViewPoint(Location, Rotation);
			Rotation = Owner->GetActorRotation();
			Rotation.Pitch = Owner->AimPitch;
			FVector COffset = Offset;
			if (!IsRightHand())
			{
				COffset.Y = -1 * COffset.Y;
			}
				
			Location += FTransform(Rotation).TransformVector(COffset);

			FVector End = PlayerController->CursorLocation;
			End -= Location;
			End.Normalize();
			UWorld* World = GetWorld();
			if (this->BulletType && World)
			{
				AXProjectile * Bullet = World->SpawnActor<AXProjectile>(this->BulletType, Location, Rotation, SpawnParams);
				if (Bullet)
				{
					Bullet->SetOwner(Owner);
					Bullet->FireInDirection(End.Rotation().Vector());
				}
			}
		}
	}
}