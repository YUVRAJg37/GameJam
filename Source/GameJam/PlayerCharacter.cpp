// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter() :
PlayerMovementFactor(30),
bSelectPressed(false),
PlayerScore(0),
JumpCounter(0),
JumpHeight(100),
DashDistance(200),
bCanDash(true),
DashDelay(0.5f),
DashStop(0.2f),
MaxDash(2.0f),
DashCoolDown(2.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(SpringArmComponent);

	SpringArmComponent->TargetArmLength = 900.0f;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 17.0f;

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetConstraintMode(EDOFMode::YZPlane);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	GetCharacterMovement()->AirControl = 1.0f;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 0, -1);

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
		GEngine->AddOnScreenDebugMessage(1, -1, FColor::Red, FString::Printf(TEXT("MaxDash : %i"), MaxDash));
		// GEngine->AddOnScreenDebugMessage(3, -1, FColor::Green, FString::Printf(TEXT("Score : %f"), PlayerScore));
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
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APlayerCharacter::Dash);
	
}

void APlayerCharacter::Movement(float Value)
{
	if(Controller!=nullptr && Value!=0)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation{0, Rotation.Yaw, 0};

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, -Value*PlayerMovementFactor*GetWorld()->DeltaTimeSeconds);
	}
}

void APlayerCharacter::PlayerJump()
{
	if(JumpCounter<=1)
	{
		ACharacter::LaunchCharacter(FVector(0,0,JumpHeight), false, true);
		JumpCounter++;
	}
}

void APlayerCharacter::SelectPressed()
{
	bSelectPressed = true;
}

void APlayerCharacter::SelectReleased()
{
	bSelectPressed = false;
}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	JumpCounter = 0;
}

void APlayerCharacter::Dash()
{
	if(bCanDash && (MaxDash>0 && MaxDash<=2))
	{
		bCanDash = false;
		GetCharacterMovement()->BrakingFriction = 0;
		GetCharacterMovement()->GravityScale = 0;
		ACharacter::LaunchCharacter(FVector(0,  GetMesh()->GetForwardVector().Y*DashDistance, 0), true, true);
		
		GetWorldTimerManager().SetTimer(DashTimeHandler, this, &APlayerCharacter::DashEnd, DashStop, false);
		GetWorldTimerManager().SetTimer(DashCoolDownIncrementHandle, this, &APlayerCharacter::DashIncrement, DashCoolDown, false);
		MaxDash--;
	}
}

void APlayerCharacter::DashEnd()
{
	GetCharacterMovement()->BrakingFriction = 2.0f;
	GetCharacterMovement()->GravityScale = 1.0f;
	GetCharacterMovement()->StopMovementImmediately();
	GetWorldTimerManager().SetTimer(DashCoolDownHandler, this, &APlayerCharacter::DashReset, DashDelay, false);
}

void APlayerCharacter::DashReset()
{
	bCanDash = true;
}

void APlayerCharacter::DashIncrement()
{
	MaxDash++;
}



