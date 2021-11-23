// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyTurret.h"
#include "PlayerCharacter.h"
#include "NormalEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API ANormalEnemy : public AEnemyTurret
{
	GENERATED_BODY()

	ANormalEnemy();
	
protected:
	
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	void EnemyLogic();
	void EnemyShoot();
	FVector EnemyMovementvector();

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Shoot, meta = (AllowPrivateAccess = "true"))
	float PlayerTargetDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Shoot, meta = (AllowPrivateAccess = "true"))
	float EnemyFireRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Shoot, meta = (AllowPrivateAccess = "true"))
	float EnemySpeedFactor;
	FTimerHandle EnemyHandle;

	APlayerCharacter* PlayerCharacter;
};
