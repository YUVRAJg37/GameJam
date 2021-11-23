// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalEnemy.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ANormalEnemy::ANormalEnemy() 
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANormalEnemy::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void ANormalEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	EnemyLogic();
}

void ANormalEnemy::EnemyLogic()
{
	
	if(bIsInRange(PlayerTargetDistance))
	{
		GetWorldTimerManager().SetTimer(EnemyHandle, this, &ANormalEnemy::EnemyShoot, EnemyFireRate);
		SetActorLocation(EnemyMovementvector());
	}
}

void ANormalEnemy::EnemyShoot()
{
	Shoot();
}

FVector ANormalEnemy::EnemyMovementvector()
{
	if(PlayerCharacter)
	{
		FVector EnemyLocation{GetActorLocation()};
		float EnemyZLocation  = EnemyLocation.Z;
		FVector DeltaLocation =  UKismetMathLibrary::VInterpTo(EnemyLocation, PlayerCharacter->GetActorLocation(), GetWorld()->DeltaTimeSeconds,EnemySpeedFactor);
		DeltaLocation.Z = EnemyZLocation;
		return DeltaLocation;
	}

	return GetActorLocation();
}
