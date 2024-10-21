// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTPM_Respawn.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Navigation/NavigationTypes.h"
#include "GameFramework/Actor.h"
#include "Navigation/PathFollowingComponent.h"

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
	
	FVector RespawnLocation = FVector(0.0f, -500.0f, 0.0f);
	AIController->MoveToLocation(RespawnLocation);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsFleeing", false);

	
	if (AIController->GetMoveStatus() == EPathFollowingStatus::Type::Idle)
	{
		//Une fois l'IA respawn, on la remet en vie
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsDead", false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsChasing", true);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}


