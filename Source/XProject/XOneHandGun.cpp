// Fill out your copyright notice in the Description page of Project Settings.

#include "XOneHandGun.h"
#include "XProjectile.h"
#include "XBaseCharacter.h"
#include "XBaseEnemyCharacter.h"
#include "XPlayerController.h"

AXOneHandGun::AXOneHandGun()
{
	Offset = FVector(50.f, 5.f, 0.f);
}

void AXOneHandGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXOneHandGun::BeginPlay()
{
	Super::BeginPlay();
}

void AXOneHandGun::OnUse(AXBaseCharacter * Character)
{
	if (!IsReloading && InMagazine > 0)
	{
		UWorld * World = GetWorld();
		AXBaseEnemyCharacter * AIOwner = Cast<AXBaseEnemyCharacter>(GetOwner());
		if (AIOwner && World)
		{
			FVector Location;
			FRotator Rotation;
			FActorSpawnParameters SpawnParams;

			AIOwner->GetActorEyesViewPoint(Location, Rotation);
			Rotation = AIOwner->GetActorRotation();
			//Rotation.Pitch = AIOwner->AimPitch;
			FVector CurrentOffset = Offset;

			//Calculate spawn location
			Location += FTransform(Rotation).TransformVector(CurrentOffset);

			//Spawn projectile
			AXProjectile * Bullet = World->SpawnActor<AXProjectile>(BulletType, Location, Rotation, SpawnParams);
			if (Bullet)
			{
				Bullet->SetOwner(AIOwner);
				//Fire projectile
				Bullet->FireInDirection(Rotation.Vector());
			}
			return;
		}

		AXBaseCharacter * Owner = Cast<AXBaseCharacter>(GetOwner());
		AXPlayerController * PlayerController = Cast<AXPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
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
				//Rotation.Pitch = Owner->AimPitch;
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
				#if WITH_EDITOR
					if (Debug)
					{
						DrawDebugLine(World, Location, End, FColor(255, 0, 0), false, -1, 0, 1);
					}
				#endif
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
	else if (!IsReloading && InMagazine <= 0) Reload();
}

void AXOneHandGun::Reload()
{
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &AXOneHandGun::PerformReload, ReloadDelay, false);
	IsReloading = true;
#if WITH_EDITOR
	if (Debug)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Reload"));
	}
#endif
}

void AXOneHandGun::PerformReload()
{
	InMagazine = MagazineSize;
	IsReloading = false;
#if WITH_EDITOR
	if (Debug)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Perform reload"));
	}
#endif
}
