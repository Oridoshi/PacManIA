// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTPM_FleePM.generated.h"

/**
 * 
 */
UCLASS()
class PACMANIA_API UBTPM_FleePM : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTPM_FleePM();

	// Override de la fonction ExecuteTask
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	AActor* GetPacMan(UBehaviorTreeComponent& OwnerComp) const;
};
