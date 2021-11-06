// Fill out your copyright notice in the Description page of Project Settings.


#include "Items.h"

// Sets default values
AItems::AItems() :
ItemRotateFactor(10.0f),
ItemScoreValue(10.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionBox = CreateDefaultSubobject<USphereComponent>("Collision Box");
	RootComponent = CollisionBox;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	ItemMesh->SetupAttachment(CollisionBox);

	ItemMesh->SetEnableGravity(false);
	ItemMesh->SetSimulatePhysics(false);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollisionBox->SetSphereRadius(10.0f);
	
}

// Called when the game starts or when spawned
void AItems::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AItems::OnBeginOverLap);
	
}

// Called every frame
void AItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ItemMesh->AddLocalRotation(FRotator{0,ItemRotateFactor*GetWorld()->GetDeltaSeconds(), 0});

}

void AItems::OnBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	
	if(PlayerCharacter)
	{
		PlayerCharacter->SetPlayerScore(ItemScoreValue);
		Destroy();
	}
	
}



