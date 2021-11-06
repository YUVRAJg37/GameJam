// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter() :
PlayerMovementFactor(30),
bSelectPressed(false),
PlayerScore(0)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetConstraintMode(EDOFMode::YZPlane);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, -1, FColor::Red, FString::Printf(TEXT("Score : %f"), PlayerScore));
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move", this, &APlayerCharacter::Movement);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::PlayerJump);
	
	PlayerInputComponent->BindAction("Select", IE_Pressed, this, &APlayerCharacter::SelectPressed);
	PlayerInputComponent->BindAction("Select", IE_Pressed, this, &APlayerCharacter::SelectReleased);
	
}

void APlayerCharacter::Movement(float Value)
{
	FVector movementVector{0, Value, 0};
	
	AddMovementInput(movementVector* PlayerMovementFactor* GetWorld()->DeltaTimeSeconds);
}

void APlayerCharacter::PlayerJump()
{
	Jump();
}

void APlayerCharacter::SelectPressed()
{
	bSelectPressed = true;
}

void APlayerCharacter::SelectReleased()
{
	bSelectPressed = false;
}


