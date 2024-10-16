// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTPM_ChasePM.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "AI/APM_Ghost.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "Player/APM_PacMan.h"

//TaskName
UBTPM_ChasePM::UBTPM_ChasePM()
{
	NodeName = "ChasePM";
}

//Task
EBTNodeResult::Type UBTPM_ChasePM::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = AIController ? AIController->GetPawn() : nullptr;
    
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}
	
	AAPM_Ghost* Ghost = Cast<AAPM_Ghost>(ControlledPawn);
	if (!Ghost)
	{
		return EBTNodeResult::Failed;
	}

	// Check if the ghost is within the ChaseDistance of Pac-Man
	AActor* PacMan = GetPacMan();
	if (PacMan && IsWithinChaseDistance(Ghost, PacMan))
	{
		MoveTowardsPacMan(AIController, PacMan);
		return EBTNodeResult::InProgress;
	}
	
	FString GhostColor = Ghost->Color;
	if(GhostColor.Equals("Red") && RedGhostMovement(AIController))
	{
		return EBTNodeResult::Succeeded;
	}
	if(GhostColor.Equals("Orange") && OrangeGhostMovement(AIController))
	{
		return EBTNodeResult::Succeeded;
	}
	if(GhostColor.Equals("Blue") && BlueGhostMovement(AIController))
	{
		return EBTNodeResult::Succeeded;
	}
	if(GhostColor.Equals("Yellow") && YellowGhostMovement(AIController))
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

//function

/*--------------Movement---------------------*/

//red
bool UBTPM_ChasePM::RedGhostMovement(AAIController* AIController)
{
	// Cherche le Pac-Man le plus proche
	AActor* PacMan = GetPacMan();

	//movement
	if (PacMan && AIController)
	{
		AIController->MoveToActor(PacMan);
		return  true;
	}
	
	return false;
}

//orange
bool UBTPM_ChasePM::OrangeGhostMovement(AAIController* AIController)
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSys && AIController)
	{
		// Vérifie si le fantôme est déjà en train de se déplacer
		if (AIController->GetMoveStatus() == EPathFollowingStatus::Type::Idle)
		{
			FNavLocation RandomLocation;
			const float SearchRadius = 1000.0f;

			if (NavSys->GetRandomPointInNavigableRadius(AIController->GetPawn()->GetActorLocation(), SearchRadius, RandomLocation))
			{
				// Déplace le fantôme vers une nouvelle destination aléatoire
				AIController->MoveToLocation(RandomLocation.Location);
				return true;
			}
		}
	}
	return false;
}

//blue
bool UBTPM_ChasePM::BlueGhostMovement(AAIController* AIController)
{
	AActor* PacMan = GetPacMan();

	if (PacMan && AIController)
	{
		FVector PacManLocation = PacMan->GetActorLocation();
		FVector PacManForwardVector = PacMan->GetActorForwardVector();

		FVector TargetLocation = PacManLocation + (PacManForwardVector * TrapDistance);
		
		AIController->MoveToLocation(TargetLocation);
		
		return true;
	}

	return false;
}

//yellow
bool UBTPM_ChasePM::YellowGhostMovement(AAIController* AIController)
{
	AAPM_Ghost* RedGhost = GetGhostByColor("Red");
	AActor* PacMan = GetPacMan();
	if (!PacMan || !RedGhost)
	{
		return false;
	}

	FVector PacManLocation = PacMan->GetActorLocation();
	FVector RedGhostLocation = RedGhost->GetActorLocation();
	FVector DirectionToRedGhost = RedGhostLocation - PacManLocation;
	DirectionToRedGhost.Normalize();
	
	FVector TargetLocation = PacManLocation - (DirectionToRedGhost * TrapDistance);

	AIController->MoveToLocation(TargetLocation);

	return true;
}

/*--------------------------------------------------------------------*/

//get ghost
AAPM_Ghost* UBTPM_ChasePM::GetGhostByColor(FString GhostColor) const
{
	TArray<AActor*> FoundGhosts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAPM_Ghost::StaticClass(), FoundGhosts);

	for (AActor* Actor : FoundGhosts)
	{
		AAPM_Ghost* Ghost = Cast<AAPM_Ghost>(Actor);
		if (Ghost && Ghost->Color.Equals(GhostColor))
		{
			return Ghost;
		}
	}
	return nullptr;
}

// Helper function to check the distance between Ghost and Pac-Man
bool UBTPM_ChasePM::IsWithinChaseDistance(AAPM_Ghost* Ghost, AActor* PacMan) const
{
	float Distance = FVector::Dist(Ghost->GetActorLocation(), PacMan->GetActorLocation());
	return Distance <= ChaseDistance;
}

//get Target PacMan
AActor* UBTPM_ChasePM::GetPacMan() const
{
	// Trouve tous les Pac-Men dans la scène
	TArray<AActor*> FoundPacMan;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAPM_PacMan::StaticClass(), FoundPacMan);

	if (FoundPacMan.Num() == 0)
	{
		return nullptr;  // Pas de Pac-Men trouvés
	}

	return  FoundPacMan[0];
}


// Movement towards Pac-Man
void UBTPM_ChasePM::MoveTowardsPacMan(AAIController* AIController, AActor* PacMan)
{
	if (!AIController || !PacMan)
	{
		return;
	}

	const float AcceptanceRadius = 30.0f; // Adjust this value if needed
	
	AIController->MoveToActor(PacMan, AcceptanceRadius, true, true, false, 0, true);
	AIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &UBTPM_ChasePM::OnMovementComplete);
}

// Callback for when the ghost finishes its movement
void UBTPM_ChasePM::OnMovementComplete(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	// Check if the movement was successfully completed
	if (Result.Code == EPathFollowingResult::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cacth"));
	}
}



