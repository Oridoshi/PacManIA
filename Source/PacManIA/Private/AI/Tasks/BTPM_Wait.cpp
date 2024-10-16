// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Tasks/BTPM_Wait.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"

UBTPM_Wait::UBTPM_Wait()
{
	NodeName = "WaitSpawn";
}

EBTNodeResult::Type UBTPM_Wait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	// Récupère le contrôleur de l'IA
	AAIController* AIController = OwnerComp.GetAIOwner();
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSys && AIController)
	{
		// Vérifie si le fantôme est déjà en train de se déplacer
		if (AIController->GetMoveStatus() == EPathFollowingStatus::Type::Idle)
		{
			FNavLocation RandomLocation;
			const float SearchRadius = 200.0f;

			if (NavSys->GetRandomPointInNavigableRadius(AIController->GetPawn()->GetActorLocation(), SearchRadius, RandomLocation))
			{
				// Déplace le fantôme vers une nouvelle destination aléatoire
				AIController->MoveToLocation(RandomLocation.Location);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}


