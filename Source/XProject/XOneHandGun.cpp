// Fill out your copyright notice in the Description page of Project Settings.

#include "XOneHandGun.h"
#include "XProjectile.h"
#include "XBaseCharacter.h"
#include "XCamera.h"
#include "XPlayerController.h"

AXOneHandGun::AXOneHandGun()
{
	Offset = FVector(50.f, 5.f, 0.f);
	UseDelay = 0.5f;
}

//void AXOneHandGun::Use(AXBaseCharacter * Character)
//{
//	if (Coldown <= 0.f)
//	{
//		OnUse(Character);
//		Coldown = OnUseColdown;
//	}
//}

void AXOneHandGun::OnUse(AXBaseCharacter * Character)
{
	AXBaseCharacter * Owner = Cast<AXBaseCharacter>(GetOwner());
	AXPlayerController * PlayerController = Cast<AXPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UWorld * World = GetWorld();
	
	if (Owner && PlayerController && World)
	{
		AXCamera * CameraActor = PlayerController->GetCamera();
		if (CameraActor && BulletType)
		{
			FVector Location;
			FRotator Rotation;
			FActorSpawnParameters SpawnParams;

			Owner->GetActorEyesViewPoint(Location, Rotation);
			Rotation = Owner->GetActorRotation();
			Rotation.Pitch = Owner->AimPitch;
			FVector CurrentOffset = Offset;

			if (!IsRightHand())
			{
				CurrentOffset.Y = -1 * CurrentOffset.Y;
			}
			//Calculate spawn location
			Location += FTransform(Rotation).TransformVector(CurrentOffset);
			//Spawn projectile
			AXProjectile * Bullet = World->SpawnActor<AXProjectile>(BulletType, Location, Rotation, SpawnParams);
			if (Bullet)
			{
				//Calculate max range base on actor and camera location
				float Max = FMath::Sqrt(
					FMath::Pow(Bullet->GetLifeSpan() * Bullet->ProjectileMovementComponent->MaxSpeed, 2) -
					FMath::Pow(Location.Z - CameraActor->GetActorLocation().Z, 2));
				FVector MaxRange = FVector(Max, 0.f, 0.f);
			
				const FName TraceTag("XGunTraceTag");
				//Debug trace line
				//World->DebugDrawTraceTag = TraceTag;

				FCollisionQueryParams ColisionParams;
				ColisionParams.bTraceComplex = true;
				ColisionParams.bTraceAsyncScene = true;
				ColisionParams.bReturnPhysicalMaterial = false;
				ColisionParams.TraceTag = TraceTag;
				//Camera location
				FRotator TraceRotation;
				FVector TraceStart;
				CameraActor->GetActorEyesViewPoint(TraceStart, TraceRotation);
				//Calculate end of trace 
				FVector TraceEnd = CameraActor->GetActorLocation() + CameraActor->GetActorRotation().RotateVector(MaxRange);
				FHitResult HitOut;
				//Create trace to find closest collision point
				World->LineTraceSingleByChannel(HitOut, TraceStart, TraceEnd, Owner->GetRootComponent()->GetCollisionObjectType(), ColisionParams);

				FVector End = TraceEnd;	//End point default is a trace end 
				//If trace hits somthing, end point is set to hit location
				if (HitOut.bBlockingHit)
				{
					End = HitOut.Location;
				}
				//For get simple vector of shoot 
				End -= Location;
				//Normalize vector
				End.Normalize();
			
				Bullet->SetOwner(Owner);
				Bullet->FireInDirection(End); 
			}
		}
	}
}

void AXOneHandGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXOneHandGun::BeginPlay()
{
	Super::BeginPlay();
}
