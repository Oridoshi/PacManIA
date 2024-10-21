// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/APM_Ghost.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "AI/APM_GhostAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameMode/GMPM_GameMode.h"

// Sets default values
AAPM_Ghost::AAPM_Ghost()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	MeshChasing = CreateDefaultSubobject<UStaticMeshComponent>("MeshChasing");
	MeshChasing->SetupAttachment(BoxCollision);

	MeshFleeing = CreateDefaultSubobject<UStaticMeshComponent>("MeshFleeing");
	MeshFleeing->SetupAttachment(BoxCollision);

	MeshDead = CreateDefaultSubobject<UStaticMeshComponent>("MeshDead");
	MeshDead->SetupAttachment(BoxCollision);

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
	
	StartLocation = GetActorLocation();

	AIController = Cast<AAPM_GhostAIController>(GetController());

	try
	{
		AGMPM_GameMode* GameMode = Cast<AGMPM_GameMode>(GetWorld()->GetAuthGameMode());

		GameMode->AddFantome(this);
		
	}
	catch (_exception)
	{
		UE_LOG(LogTemp, Error, TEXT("Error: GameMode is not valid"));
		
	}

	//comme ça fonctionne pas on force comme des connards
	if (!MovementComponent)
	{
		MovementComponent = NewObject<UFloatingPawnMovement>(this, TEXT("FloatingPawnMovement"));
		MovementComponent->UpdatedComponent = BoxCollision;
	}

	//Default Ghost Speed
	SetGhostSpeed(800.0);
}

// Called every frame
void AAPM_Ghost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(AIController)
	{
		if(AIController->BlackboardComponent->GetValueAsBool("IsChasing"))
		{
			MeshDead->SetVisibility(false);
			MeshFleeing->SetVisibility(false);
			MeshChasing->SetVisibility(true);
		}
		else if(AIController->BlackboardComponent->GetValueAsBool("IsFleeing"))
		{
			MeshDead->SetVisibility(false);
			MeshFleeing->SetVisibility(true);
			MeshChasing->SetVisibility(false);
		}
		else if(AIController->BlackboardComponent->GetValueAsBool("IsDead"))
		{
			MeshDead->SetVisibility(true);
			MeshFleeing->SetVisibility(false);
			MeshChasing->SetVisibility(false);
		}
		
		
	}
}

// Called to bind functionality to input
void AAPM_Ghost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAPM_Ghost::ResetLocation()
{
	SetActorLocation(StartLocation);
}

