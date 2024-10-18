#include "GameMode/GMPM_GameMode.h"

#include "AI/APM_Ghost.h"
#include "AI/APM_GhostAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameInstance/APM_GameInstance.h"
#include "Kismet/GameplayStatics.h"


AGMPM_GameMode::AGMPM_GameMode()
{
	
	// Initialisation de NbVieRestante avec NbVie
	GameInstance = Cast<UAPM_GameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance)
	{
		if(GameInstance->NbVieRestante <= -1)
		{
			GameInstance->NbVieRestante = NbVie;
			GameInstance->Score = 0;
		}
	}
}

void AGMPM_GameMode::AddPacGum(class AAPM_PacGum* PacGum)
{
	PacGums.Add(PacGum);
}

void AGMPM_GameMode::AddFantome(class AAPM_Ghost* Fantome)
{
	Fantomes.Add(Fantome);
}

void AGMPM_GameMode::PacGumMange(AAPM_PacGum* PacGum)
{
	GameInstance->Score += NbPointPacGum;
	PacGums.Remove(PacGum);
	
	VerifFinGame();
}

void AGMPM_GameMode::SuperPacGumMange(AAPM_PacGum* SPacGum)
{
	GameInstance->Score += NbPointSuperPacGum;
	PacGums.Remove(SPacGum);

	VerifFinGame();
}

void AGMPM_GameMode::FantomeMange()
{
	GameInstance->Score += NbPointFantome * Multiplicateur;
	Multiplicateur += AugmentationMultiplicateur;
}

void AGMPM_GameMode::ResetMultiplicateur()
{
	Multiplicateur = 1;
}

void AGMPM_GameMode::PacmanMort() const
{
	GameInstance->NbVieRestante--;
	
	if (GameInstance->NbVieRestante <= 0)
	{
		// Game Over
		UE_LOG(LogTemp, Warning, TEXT("Game Over !"));
		for (auto Fantome : Fantomes)
		{
			Fantome->ResetLocation();
			auto GhostAIController = Cast<AAPM_GhostAIController>(Cast<AAPM_Ghost>(Fantome)->GetController());
			if (GhostAIController)
			{
				GhostAIController->BlackboardComponent->SetValueAsBool("IsDead", false);
				GhostAIController->BlackboardComponent->SetValueAsBool("IsFleeing", false);
				GhostAIController->BlackboardComponent->SetValueAsBool("IsChasing", false);
			}

			GameInstance->NbVieRestante = -1;

			PacMan->Destroy();
		}
	}
	else
	{
		if (LevelPacMan.IsValid())
		{
			// Réinitialise la position du PacMan et des Fantômes
			PacMan->ResetLocation();
			
			for (auto Fantome : Fantomes)
			{
				Fantome->ResetLocation();
				auto GhostAIController = Cast<AAPM_GhostAIController>(Cast<AAPM_Ghost>(Fantome)->GetController());
				if (GhostAIController)
				{
					GhostAIController->BlackboardComponent->SetValueAsBool("IsDead", false);
					GhostAIController->BlackboardComponent->SetValueAsBool("IsFleeing", false);
					GhostAIController->BlackboardComponent->SetValueAsBool("IsChasing", false);
					GhostAIController->BlackboardComponent->SetValueAsBool("IsChasing", true);
				}
			}
			UE_LOG(LogTemp, Error, TEXT("Reset Game"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Error: LevelPacMan is not valid"));
		}
	}
}

void AGMPM_GameMode::VerifFinGame() const
{
	if (PacGums.Num() == 0)
	{
		if(GameInstance->NbVieRestante < 3)
        {
			GameInstance->NbVieRestante++;
        }
		UGameplayStatics::OpenLevel(this, FName(*LevelPacMan->GetName()), false);
	}
}

