// Fill out your copyright notice in the Description page of Project Settings.

#include "XTwoHandGun.h"
#include "XProjectile.h"
#include "XBaseCharacter.h"
#include "XBaseEnemyCharacter.h"
#include "XPlayerController.h"

AXTwoHandGun::AXTwoHandGun()
{
	// Czy character ma wywowylac metode Tick()
	PrimaryActorTick.bCanEverTick = true;
	Offset = FVector(50.f, 0.f, 0.f);
	MagazineSize = 20;
	InMagazine = MagazineSize;
	ReloadDelay = 0.5f;
	IsReloading = false;
#if WITH_EDITOR
	Debug = false;
#endif
}

void AXTwoHandGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXTwoHandGun::BeginPlay()
{
	Super::BeginPlay();
}

void AXTwoHandGun::OnUse(AXBaseCharacter * Character)
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
					//End point default is a trace end 
					FVector End = TraceEnd;
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
					//Setup projectile owner
					Bullet->SetOwner(Owner);
					//Fire projectile
					Bullet->FireInDirection(End);
				}
			}
		}
		InMagazine--;
	}
	else if (!IsReloading && InMagazine <= 0) Reload();
}

void AXTwoHandGun::Reload()
{
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &AXTwoHandGun::PerformReload, ReloadDelay, false);
	IsReloading = true;
#if WITH_EDITOR
	if (Debug)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Reload"));
	}
#endif
}

void AXTwoHandGun::PerformReload()
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
