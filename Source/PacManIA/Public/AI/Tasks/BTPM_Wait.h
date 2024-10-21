// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTPM_Wait.generated.h"

/**
 * 
 */
UCLASS()
class PACMANIA_API UBTPM_Wait : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTPM_Wait();

	// Override de la fonction ExecuteTask
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
