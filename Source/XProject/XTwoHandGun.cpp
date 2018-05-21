// Fill out your copyright notice in the Description page of Project Settings.

#include "XTwoHandGun.h"
#include "XProjectile.h"
#include "XBaseCharacter.h"
#include "XPlayerController.h"

AXTwoHandGun::AXTwoHandGun()
{
	// Czy character ma wywowylac metode Tick()
	PrimaryActorTick.bCanEverTick = true;
	Offset = FVector(50.f, 0.f, 0.f);
	ReloadDelay = 0.5f;
}

//void AXTwoHandGun::Use(AXBaseCharacter * Character)
//{
//}

void AXTwoHandGun::OnUse(AXBaseCharacter * Character)
{
	AXBaseCharacter * Owner = Cast<AXBaseCharacter>(GetOwner());
	AXPlayerController * PlayerController = Cast<AXPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UWorld * World = GetWorld();

	if (Owner && PlayerController && World)
	{
		AXCamera * CameraActor = PlayerController->GetCamera();
		if (CameraActor)
		{
			if (this->BulletType)
			{
				FVector Location;
				FRotator Rotation;
				FActorSpawnParameters SpawnParams;

				Owner->GetActorEyesViewPoint(Location, Rotation);
				Rotation = Owner->GetActorRotation();
				Rotation.Pitch = Owner->AimPitch;
				FVector COffset = Offset;

				Location += FTransform(Rotation).TransformVector(COffset);

				AXProjectile * Bullet = World->SpawnActor<AXProjectile>(this->BulletType, Location, Rotation, SpawnParams);

				float Max = FMath::Sqrt(
					FMath::Pow(Bullet->GetLifeSpan() * Bullet->ProjectileMovementComponent->MaxSpeed, 2) -
					FMath::Pow(Location.Z - CameraActor->GetActorLocation().Z, 2));
				FVector MaxRange = FVector(Max, 0.f, 0.f);

				const FName TraceTag("XTraceTag");

				//World->DebugDrawTraceTag = TraceTag;

				FCollisionQueryParams ColParams;
				ColParams.bTraceComplex = true;
				ColParams.bTraceAsyncScene = true;
				ColParams.bReturnPhysicalMaterial = false;
				ColParams.TraceTag = TraceTag;

				FRotator TraceRotation;
				FVector TraceStart;
				CameraActor->GetActorEyesViewPoint(TraceStart, TraceRotation);

				FVector TraceEnd = CameraActor->GetActorLocation() + CameraActor->GetActorRotation().RotateVector(MaxRange);
				FHitResult HitOut;
				World->LineTraceSingleByChannel(HitOut, TraceStart, TraceEnd, Owner->GetRootComponent()->GetCollisionObjectType(), ColParams);

				FVector End = TraceEnd;
				if (HitOut.bBlockingHit)
				{
					End = HitOut.Location;
				}
				End -= Location;
				End.Normalize();
				if (Bullet)
				{
					Bullet->SetOwner(Owner);
					Bullet->FireInDirection(Rotation.Vector());
				}
			}
		}
	}
}

void AXTwoHandGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXTwoHandGun::BeginPlay()
{
	Super::BeginPlay();

}
