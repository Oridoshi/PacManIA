// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/APM_MurTP.h"
#include "Player/APM_PacMan.h"

#include "Components/BoxComponent.h"
#include "GameFramework/PawnMovementComponent.h"


// Sets default values
AAPM_MurTP::AAPM_MurTP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void AAPM_MurTP::BeginPlay()
{
	Super::BeginPlay();

	this->OnActorBeginOverlap.AddDynamic(this, &AAPM_MurTP::OnOverlap);
	
	
}

// Called every frame
void AAPM_MurTP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAPM_MurTP::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	if(TargetPoint == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Error: TargetPoint TP is null"));
		return;
	}
	
	FVector TpLocationPacMan = TargetPoint->GetActorLocation();
	OtherActor->SetActorLocation(TpLocationPacMan, false, nullptr, ETeleportType::ResetPhysics);

}

