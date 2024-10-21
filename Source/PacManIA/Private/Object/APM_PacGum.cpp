// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/APM_PacGum.h"
#include "GameMode/GMPM_GameMode.h"

#include "Components/BoxComponent.h"

// Sets default values
AAPM_PacGum::AAPM_PacGum()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(BoxCollision);

}

// Called when the game starts or when spawned
void AAPM_PacGum::BeginPlay()
{
	Super::BeginPlay();

	try
	{
		GameMode = Cast<AGMPM_GameMode>(GetWorld()->GetAuthGameMode());
		
	}
	catch (_exception)
	{
		UE_LOG(LogTemp, Error, TEXT("Error: GameMode is not valid"));
		
	}

	GameMode->AddPacGum(this);
	
}

// Called every frame
void AAPM_PacGum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

