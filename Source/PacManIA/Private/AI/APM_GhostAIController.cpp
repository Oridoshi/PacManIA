// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/APM_GhostAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AAPM_GhostAIController::AAPM_GhostAIController()
{
	// Initialisation des composants Blackboard et BehaviorTree
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void AAPM_GhostAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AAPM_GhostAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Démarrer le Behavior Tree si disponible
	if (BehaviorTree)
	{
		if (BlackboardComponent)
		{
			BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		}
		BehaviorTreeComponent->StartTree(*BehaviorTree);
	}
}