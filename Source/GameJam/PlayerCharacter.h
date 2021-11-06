// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GAMEJAM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement , meta=(AllowPrivateAccess = "true"))
	float PlayerMovementFactor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement , meta=(AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement , meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	bool bSelectPressed;

	float PlayerScore;

protected:

	void Movement(float Value);
	void PlayerJump();

	void SelectPressed();
	void SelectReleased();

public:

	FORCEINLINE bool GetIsSelectPressed(){return bSelectPressed;}
	FORCEINLINE float GetPlayerScore(){return PlayerScore;}
	FORCEINLINE void SetPlayerScore(float Value){PlayerScore+=Value;}

};
