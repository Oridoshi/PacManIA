#include "AI/Tasks/BTPM_FleePM.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Player/APM_PacMan.h"
#include "NavigationSystem.h"
#include "Math/Vector.h"

UBTPM_FleePM::UBTPM_FleePM()
{
	NodeName = "FleePM";
}

EBTNodeResult::Type UBTPM_FleePM::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	// Cherche le Pac-Man le plus proche
	AActor* PacMan = GetPacMan(OwnerComp);

	// Si aucun Pac-Man n'est trouvé, échoue
	if (!PacMan)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject("TargetActor", PacMan); 
	}
	
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		// Obtenir la position actuelle de l'IA et celle de Pac-Man
		FVector PacManLocation = PacMan->GetActorLocation();
		FVector AILocation = AIController->GetPawn()->GetActorLocation();

		// Calculer la direction opposée
		FVector FleeDirection = (AILocation - PacManLocation).GetSafeNormal();

		// Calculer un point éloigné dans cette direction (par exemple, 1000 unités)
		FVector FleeDestination = AILocation + FleeDirection * 1000.0f;

		// Utiliser le système de navigation pour vérifier que le point est valide
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
		FNavLocation NavLocation;

		if (NavSys && NavSys->GetRandomPointInNavigableRadius(FleeDestination, 500.0f, NavLocation))
		{
			// Déplacer l'IA vers le point de fuite
			AIController->MoveToLocation(NavLocation.Location);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

AActor* UBTPM_FleePM::GetPacMan(UBehaviorTreeComponent& OwnerComp) const
{
	// Trouve tous les Pac-Men dans la scène
	TArray<AActor*> FoundPacMan;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAPM_PacMan::StaticClass(), FoundPacMan);

	if (FoundPacMan.Num() == 0)
	{
		return nullptr;  // Pas de Pac-Men trouvés
	}

	return  FoundPacMan[0];
}
