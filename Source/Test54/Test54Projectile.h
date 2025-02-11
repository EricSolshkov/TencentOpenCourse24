// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Test54Projectile.generated.h"

class UScoreBoard;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class ATest54Projectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UScoreBoard* ScoreBoard;

	// def an event with two parameters, called FOnProjectileHit
	DECLARE_EVENT_TwoParams(ATest54Projectile, FOnProjectileHit, ATest54Projectile*, AActor*);
	
	FOnProjectileHit OnProjectileHit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APawn* Emitter;	

public:
	ATest54Projectile();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

