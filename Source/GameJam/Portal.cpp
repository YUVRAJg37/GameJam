// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"

// #include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("Collision Box");
	CollisionBox->SetupAttachment(GetRootComponent());
	
	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>("Portal Mesh");
	PortalMesh->SetupAttachment(CollisionBox);

	PortalExitComponent = CreateDefaultSubobject<USceneComponent>("Portal Exit");
	PortalExitComponent->SetupAttachment(CollisionBox);
	
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnBeginOverlap);
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

	if(PlayerCharacter)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), PortalClass, PortalArray);
		for(int32 i=0; i<PortalArray.Num(); i++)
		{
			APortal* Portal = Cast<APortal>(PortalArray[i]);
			if(Portal)
			{
				if((Portal->GetPortalIndex() == PortalIndex) && !Portal->bEntrance && bEntrance)
				{
					PlayerCharacter->SetActorLocation(Portal->PortalExitComponent->GetComponentLocation());
					break;
				}
				if((Portal->GetPortalIndex() == PortalIndex) && !bEntrance && Portal->bEntrance)
				{
					PlayerCharacter->SetActorLocation(Portal->PortalExitComponent->GetComponentLocation());
					break;
				}
			}
		}
	}
}
	
