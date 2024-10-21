// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/APM_Ghost.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Navigation/PathFollowingComponent.h"
#include "BTPM_ChasePM.generated.h"


/**
 * 
 */
UCLASS()
class PACMANIA_API UBTPM_ChasePM : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTPM_ChasePM();

	// Override de la fonction ExecuteTask
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void MoveTowardsPacMan(AAIController* AIController, AActor* PacMan);
	void OnMovementComplete(FAIRequestID RequestID, const FPathFollowingResult& Result);

	AActor* GetPacMan() const;
	AAPM_Ghost* GetGhostByColor(FString GhostColor) const;
	bool IsWithinChaseDistance(AAPM_Ghost* Ghost, AActor* PacMan) const;

	bool RedGhostMovement(AAIController* AIController);
	bool OrangeGhostMovement(AAIController* AIController);
	bool BlueGhostMovement(AAIController* AIController);
	bool YellowGhostMovement(AAIController* AIController);

	FVector ShouldUseTeleporter(FVector GhostLocation, FVector PacManLocation);
	void MoveTo(AAIController* AIController, FVector TargetLocation);

	float TrapDistance = 300.0;
	float ChaseDistance = 500.0;
};
