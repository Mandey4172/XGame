// Fill out your copyright notice in the Description page of Project Settings.

#include "XProjectile.h"
#include "XBaseCharacter.h"
#include "Core.h"

// Sets default values
AXProjectile::AXProjectile()
{
	// Uzywaj komponentu poruszania sie pocisku do opisu ruchu pocisku
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(GetCollisionComponent());
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->bAutoUpdateTickRegistration = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
	
	// Uwanie komponentu statycznej siatki do opisu wygladu pocisu
	ActorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	ActorMeshComponent->AttachTo(GetCollisionComponent());
	// Zniszcz po 
	InitialLifeSpan = 30.0f;
}

// Called when the game starts or when spawned
void AXProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AXProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor != this)
	{
		//Sprawdzanie czy Actor to nasza postac [Rzutowanie actora na AGCharacter i sprawdzenie czy zrzutowany obiek nie jest null]
		AXBaseCharacter * HitCharacter = Cast<AXBaseCharacter>(OtherActor);
		AActor * Owner = this->GetOwner();
		if (HitCharacter  && HitCharacter != Owner)
		{
			//Zadanie obrazen
			HitCharacter->InflictDamage(this->Damage, Hit);
		}
		SetLifeSpan(0.000001f);
	}
}

void AXProjectile::FireInDirection(const FVector & ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AXProjectile::OnCollision(AActor * OtherActor, const FHitResult & SweepResult)
{
	//Odbicie pocisku
	/*FVector N = OtherActor->GetActorLocation() - GetActorLocation();
	N.Z = 0;
	FVector V = ProjectileMovementComponent->Velocity;
	FVector R = V - (2 * V.ProjectOnTo(N));
	ProjectileMovementComponent->Velocity = R;*/
	Destroy();
}

