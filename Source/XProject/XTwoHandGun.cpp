// Fill out your copyright notice in the Description page of Project Settings.

#include "XTwoHandGun.h"
#include "XProjectile.h"
#include "XBaseCharacter.h"
#include "XPlayerController.h"

AXTwoHandGun::AXTwoHandGun()
{
	Offset = FVector(50.f, 0.f, 0.f);
}

void AXTwoHandGun::Use()
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
			Location += FTransform(Rotation).TransformVector(Offset);

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
