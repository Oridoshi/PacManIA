// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "APM_GhostAIController.generated.h"

/**
 * 
 */
UCLASS()
class PACMANIA_API AAPM_GhostAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UBlackboardComponent* BlackboardComponent;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UBehaviorTreeComponent* BehaviorTreeComponent;

public:
	AAPM_GhostAIController();

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	
};
