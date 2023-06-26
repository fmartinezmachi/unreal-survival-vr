// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn_CPP.h"

// Sets default values
AVRPawn_CPP::AVRPawn_CPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVRPawn_CPP::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("HOLA MUNDO"));
	UE_LOG(LogTemp, Log, TEXT("VIDA: %d"), Health);
	
}

// Called every frame
void AVRPawn_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPawn_CPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

