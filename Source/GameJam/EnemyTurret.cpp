// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTurret.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyTurret::AEnemyTurret() :
TargetDistance(500.0f),
FireRate(1.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	TurretMesh->SetupAttachment(GetRootComponent());
	
}

// Called when the game starts or when spawned
void AEnemyTurret::BeginPlay()
{
	Super::BeginPlay();
	
	TurretLogic();
}

// Called every frame
void AEnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AEnemyTurret::bIsInRange(float Range)
{
	APlayerCharacter* playerCharacter;
	playerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if(playerCharacter)
	{
		if(FVector::Dist(playerCharacter->GetActorLocation(), GetActorLocation()) <= Range)
		{
			return true;
		}
	}

	return false;
}

void AEnemyTurret::Shoot()
{
		UE_LOG(LogTemp, Warning, TEXT("Pew Pew"));
}

void AEnemyTurret::TurretLogic()
{
	GetWorldTimerManager().SetTimer(TurretHandle, this, &AEnemyTurret::TurretLogic, FireRate);
	if(bIsInRange(TargetDistance))
	{
		Shoot();
	}
}

