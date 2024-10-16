// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/APM_Ghost.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "AI/APM_GhostAIController.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AAPM_Ghost::AAPM_Ghost()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(BoxCollision);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	MovementComponent->UpdatedComponent = BoxCollision;

	AIControllerClass = AAPM_GhostAIController::StaticClass();
}

void AAPM_Ghost::SetGhostSpeed(float NewSpeed)
{
	if (MovementComponent)
	{
		MovementComponent->MaxSpeed = NewSpeed;
	}
}

// Called when the game starts or when spawned
void AAPM_Ghost::BeginPlay()
{
	Super::BeginPlay();

	//comme ça fonctionne pas on force comme des connards
	if (!MovementComponent)
	{
		MovementComponent = NewObject<UFloatingPawnMovement>(this, TEXT("FloatingPawnMovement"));
		MovementComponent->UpdatedComponent = BoxCollision;
	}

	//Default Ghost Speed
	SetGhostSpeed(600.0);
}

// Called every frame
void AAPM_Ghost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAPM_Ghost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

