// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XTwoHandWeapon.h"
#include "XGun.h"
#include "XTwoHandGun.generated.h"

/**
 * 
 */
UCLASS()
class XPROJECT_API AXTwoHandGun : public AXTwoHandWeapon
{
	GENERATED_BODY()
	
public:

	AXTwoHandGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*UFUNCTION(BlueprintCallable)
	virtual void Use(class AXBaseCharacter * Character) override;*/

	virtual void OnUse(class AXBaseCharacter * Character) override;

	UFUNCTION(BlueprintCallable)
	void Reload();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AXProjectile> BulletType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MagazineSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ReloadDelay;

private:

	FTimerHandle ReloadTimer;
	bool IsReloading;
	void PerformReload();
	int InMagazine;

#if WITH_EDITOR
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Debug;

#endif
};
