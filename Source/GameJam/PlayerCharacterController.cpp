// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacterController::APlayerCharacterController()
{
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	// TArray<AActor*> cameraActor;
	// UGameplayStatics::GetAllActorsOfClass(GetWorld() ,ACameraActor::StaticClass(), cameraActor);
	//
	// FViewTargetTransitionParams TransitionParams;
	// SetViewTarget(cameraActor[0], TransitionParams);
	
}
