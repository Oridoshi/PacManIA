#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Player/APM_PacMan.h"
#include "GMPM_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class PACMANIA_API AGMPM_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AGMPM_GameMode(); // Déclaration du constructeur
	
	UFUNCTION()
	void AddPacGum(class AAPM_PacGum* PacGum); // Déclaration de la fonction AddPackGum

	UFUNCTION()
	void AddFantome(class AAPM_Ghost* Fantome); // Déclaration de la fonction AddFantome

	UPROPERTY()
	AAPM_PacMan * PacMan; // Déclaration de la variable PacMan

	/**
	 * Nombre de vie au début de la partie
	 * @note: La valeur doit être supérieure ou égale à 1
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Regle", meta = (ClampMin = "1.0"))
	int NbVie = 3;

	/**
	 * Nombre de points gagnés lorsqu'on mange une pac-gum
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Regle")
	int NbPointPacGum = 10;

	/**
	 * Nombre de points gagnés lorsqu'on mange une super pac-gum
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Regle")
	int NbPointSuperPacGum = 50;

	/**
	 * Nombre de points gagnés lorsqu'on mange un fantôme
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Regle")
	int NbPointFantome = 100;

	/**
	 * Multiplicateur de score lorsqu'on mange un fantôme
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Regle")
	int AugmentationMultiplicateur = 1;

	/**
	 * Multiplicateur de score
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Regle")
	int Multiplicateur = 1;

	/**
	 * Fichier Level PacMan
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Parametre")
	TSoftObjectPtr<UWorld> LevelPacMan;

	/**
	 * GameInstance
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Parametre")
	class UAPM_GameInstance* GameInstance;
	
	/************************************/
	/* Fonctions de gestion du score    */
	/************************************/
	
	/**
	 * Une PacGum a été mangée
	 */
	UFUNCTION()
	void PacGumMange(AAPM_PacGum* PacGum);

	/**
	 * Une SuperPacGum a été mangée
	 */
	UFUNCTION()
	void SuperPacGumMange(AAPM_PacGum* SPacGum);

	/**
	 * Un fantôme a été mangé
	 */
	UFUNCTION()
	void FantomeMange();

	/**
	 * Réinitialiser le multiplicateur
	 */
	UFUNCTION()
	void ResetMultiplicateur();

	/**
	 * Pacman est mort
	 */
	UFUNCTION()
	void PacmanMort() const;

private:
	/**
	 * Liste des PacGum
	 */
	UPROPERTY()
	TArray<class AAPM_PacGum*> PacGums;
	void VerifFinGame() const;

	TArray<class AAPM_Ghost*> Fantomes;
	
};
