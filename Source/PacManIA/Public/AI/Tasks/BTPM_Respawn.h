// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Navigation/PathFollowingComponent.h"
#include "BTPM_Respawn.generated.h"

/**
 * 
 */
UCLASS()
class PACMANIA_API UBTPM_Respawn : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTPM_Respawn();

	// Override de la fonction ExecuteTask
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

private:
	UBehaviorTreeComponent* MyOwnerComp;

};
