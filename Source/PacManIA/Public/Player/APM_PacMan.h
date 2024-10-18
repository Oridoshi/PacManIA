// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "APM_PacMan.generated.h"

UCLASS()
class PACMANIA_API AAPM_PacMan : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAPM_PacMan();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	UAudioComponent* AudioComponentAmbiance;

	/**
	 * Vitese de déplacement du PacMan
	 * @note: La valeur doit être supérieur  ou égale à 100
	 */
	UPROPERTY(EditAnywhere, Category="Mouvement", meta = (ClampMin = "100.0"))
	float Speed = 300;

	/**
	 * Multiplicateur de vitesse du PacMan lorsqu'il mange une super pac-gum
	 * @note: La valeur doit être supérieur  ou égale à 1
	 */
	UPROPERTY(EditAnywhere, Category="Mouvement", meta = (ClampMin = "1.0"))
	float SpeedMultiplierSuperPacMan = 2;
	
	/**
	 * Temps de super pac en seconde
	 */
	UPROPERTY(EditAnywhere, Category="Mouvement")
	float SuperPacManTime = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* MangePacGumSound1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* MangePacGumSound2;

	UPROPERTY()
	bool MangePacGumSound = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* MangeSuperPacGumSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* MangeFantomeSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* MortSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* AmbianceMusic;

	
	UPROPERTY()
	class AGMPM_GameMode* GameMode;

	UPROPERTY()
	bool IsSuperPacMan = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveX(float Value);
	
	void MoveY(float Value);
	void Rotate();

private:
	UFUNCTION()
	void OnOverlap(AActor* MyActor, AActor* OtherActor);

	UFUNCTION()
	void SuperPacMan();

	UFUNCTION()
	void SuperPacManEnd();

	UPROPERTY()
	float InputY;

	UPROPERTY()
	float InputX;

	UPROPERTY()
	FTimerHandle SuperPacManTimerHandle;

	UFUNCTION()
	void HandleLoopingSound();

private:
	/**
	 * Emplacement de départ
	 */
	UPROPERTY()
	FVector StartLocation;

public:
	UFUNCTION()
	void ResetLocation();
	
};
