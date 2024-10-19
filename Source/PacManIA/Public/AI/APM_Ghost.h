// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "APM_GhostAIController.h"
#include "GameFramework/Pawn.h"
#include "APM_Ghost.generated.h"

UCLASS()
class PACMANIA_API AAPM_Ghost : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshChasing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshFleeing;
    	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* MovementComponent;


public:
	// Sets default values for this pawn's properties
	AAPM_Ghost();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Color", meta = (AllowPrivateAccess = "true"))
	FString Color;

	void SetGhostSpeed(float NewSpeed);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/**
	 * Emplacement de départ
	 */
	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	AAPM_GhostAIController* AIController;

public:
	UFUNCTION()
	void ResetLocation();

};