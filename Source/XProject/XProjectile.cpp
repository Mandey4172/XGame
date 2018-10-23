// Fill out your copyright notice in the Description page of Project Settings.

#include "XProjectile.h"
#include "XBaseCharacter.h"
#include "Core.h"

// Sets default values
AXProjectile::AXProjectile()
{
	//
	SphareCollisionComponent->SetGenerateOverlapEvents(true);
	SphareCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AXProjectile::BeginOverlap);
	SphareCollisionComponent->OnComponentHit.AddDynamic(this, &AXProjectile::OnHit);

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
	ActorMeshComponent->SetupAttachment(GetCollisionComponent());
	// Zniszcz po 
	InitialLifeSpan = 100.0f;
}

// Called when the game starts or when spawned
void AXProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AXProjectile::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != this)
	{
		Destroy();
	}
}

void AXProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor != this)
	{
		//Sprawdzanie czy Actor to nasza postac [Rzutowanie actora na AGCharacter i sprawdzenie czy zrzutowany obiek nie jest null]
		AXBaseCharacter * HitCharacter = Cast<AXBaseCharacter>(OtherActor);
		AActor * Owner = GetOwner();
		if (HitCharacter  && HitCharacter != Owner)
		{
			//Zadanie obrazen
			HitCharacter->InflictDamage(Damage, Hit);
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
	Destroy();
}

