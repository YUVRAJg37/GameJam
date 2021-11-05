// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class GAMEJAM_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* PortalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components, meta=(AllowPrivateAccess = "true"))
	USceneComponent* PortalExitComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* CollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<APortal> PortalClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta=(AllowPrivateAccess = "true"))
	TArray<AActor*> PortalArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PortalValues, meta=(AllowPrivateAccess = "true"))
	bool bEntrance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PortalValues, meta=(AllowPrivateAccess = "true"))
	int32 PortalIndex;

protected:

	
public:

	FORCEINLINE int32 GetPortalIndex(){return PortalIndex;}
	FORCEINLINE USceneComponent* GetPortalExitLocationMesh(){return PortalExitComponent;}
};
