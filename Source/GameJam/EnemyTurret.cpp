// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTurret.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyTurret::AEnemyTurret() :
TargetDistance(500.0f)
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

	
	
}

// Called every frame
void AEnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Shoot();

}

bool AEnemyTurret::bIsInRange()
{
	APlayerCharacter* playerCharacter;
	playerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if(playerCharacter)
	{
		if(FVector::Dist(playerCharacter->GetActorLocation(), GetActorLocation()) <= TargetDistance)
		{
			return true;
		}
	}

	return false;
}

void AEnemyTurret::Shoot()
{
	if(bIsInRange())
	{
		UE_LOG(LogTemp, Warning, TEXT("Pew Pew"));
	}
	
}

