// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTPM_Respawn.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "NavigationSystem.h"

UBTPM_Respawn::UBTPM_Respawn()
{
	NodeName = "Respawn";
}

EBTNodeResult::Type UBTPM_Respawn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Récupère le contrôleur de l'IA
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	// Déplacer l'IA vers la position (0, 0, 0)
	FVector RespawnLocation = FVector(0.0f, -500.0f, 0.0f);
	AIController->MoveToLocation(RespawnLocation);

	return EBTNodeResult::Succeeded;
}


