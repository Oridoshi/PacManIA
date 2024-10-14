// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GMPM_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class PACMANIA_API AGMPM_GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	/**
	 * Score du joueur
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Score")
	int Score = 0;

	/**
	 * Nombre de vie au début de la partie
	 * @note: La valeur doit être supérieur ou égale à 1
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Regle", meta = (ClampMin = "1.0"))
	int NbVie = 3;

	/**
	 * Nombre de vie restante
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Regle")
	int NbVieRestante = NbVie;

	/**
	 * Nombre de point gagné lorsqu'on mange un pac-gum
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Regle")
	int NbPointPacGum = 10;

	/**
	 * Nombre de point gagné lorsqu'on mange un super pac-gum
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Regle")
	int NbPointSuperPacGum = 50;

	/**
	 * Nombre de point gagné lorsqu'on mange un fantome
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Regle")
	int NbPointFantome = 100;

	/**
	 * Mutiplicateur de score lorsqu'on mange un fantome
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Regle")
	int AugmentationMultiplicateur = 1;

	/**
	 * Multiplicateur de score
	 */
	UPROPERTY()
	int Multiplicateur = 1;

	/************************************/
	/* Fonctions de gestion du score    */
	/************************************/
	
	/**
	 * Une PacGum a été mangé
	 */
	UFUNCTION()
	void PacGumMange();

	/**
	 * Une SuperPacGum a été mangé
	 */
	UFUNCTION()
	void SuperPacGumMange();

	/**
	 * Un fantome a été mangé
	 */
	UFUNCTION()
	void FantomeMange();

	/**
	 * Reset Multiplicateur
	 */
	UFUNCTION()
	void ResetMultiplicateur();
	
};
