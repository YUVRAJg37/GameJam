// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Items.generated.h"

UCLASS()
class GAMEJAM_API AItems : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItems();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components, meta=(AllowPrivateAccess = "true"))	
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components, meta=(AllowPrivateAccess = "true"))
	USphereComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Properties, meta=(AllowPrivateAccess = "true"))
	float ItemRotateFactor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Properties, meta=(AllowPrivateAccess = "true"))
	float ItemScoreValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Properties, meta=(AllowPrivateAccess = "true"))
	float InterpSpeed;

	bool bInterping;
	
protected:

	APlayerCharacter* PlayerCharacter;

	void InterpPosition(float DeltaTime);

public:

};
