// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/APM_PacMan.h"

// Sets default values
AAPM_PacMan::AAPM_PacMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAPM_PacMan::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAPM_PacMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAPM_PacMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

