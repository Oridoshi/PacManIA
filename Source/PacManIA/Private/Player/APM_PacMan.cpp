// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/APM_PacMan.h"
#include "Object/APM_PacGum.h"
#include "GameMode/GMPM_GameMode.h"
#include "AI/APM_Ghost.h"
#include "AI/APM_GhostAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAPM_PacMan::AAPM_PacMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(BoxCollision);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);

	AudioComponentAmbiance = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponentAmbiance"));
	AudioComponentAmbiance->SetupAttachment(RootComponent);

}


// Called when the game starts or when spawned
void AAPM_PacMan::BeginPlay()
{
	Super::BeginPlay();

	try
	{
		GameMode = Cast<AGMPM_GameMode>(GetWorld()->GetAuthGameMode());

		GameMode->PacMan = this;
		
	}
	catch (_exception)
	{
		UE_LOG(LogTemp, Error, TEXT("Error: GameMode is not valid"));
		
	}

	StartLocation = GetActorLocation();
	
	if (AmbianceMusic)
	{
		AudioComponentAmbiance = NewObject<UAudioComponent>(this);
		AudioComponentAmbiance->bAutoActivate = false;  // On n'active pas automatiquement, on joue manuellement
		AudioComponentAmbiance->SetSound(AmbianceMusic);
		AudioComponentAmbiance->RegisterComponent();  // Nécessaire pour les composants créés dynamiquement

		AudioComponentAmbiance->SetVolumeMultiplier(0.3);

		// Configurer le son pour qu'il boucle
		AudioComponentAmbiance->OnAudioFinished.AddDynamic(this, &AAPM_PacMan::HandleLoopingSound);

		// Jouer la musique d'ambiance
		if (!AudioComponentAmbiance->IsPlaying())
		{
			AudioComponentAmbiance->Play();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error: AudioComponentAmbiance or AmbianceMusic is not valid"));
	}
	
	AudioComponent->SetPitchMultiplier(2);
}

void AAPM_PacMan::HandleLoopingSound()
{
	if (AudioComponentAmbiance && !AudioComponentAmbiance->IsPlaying())
	{
		AudioComponentAmbiance->Play();  // Rejouer la musique lorsque le son est terminé
	}
}

// Called every frame
void AAPM_PacMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

// Called to bind functionality to input
void AAPM_PacMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Mouvement
	PlayerInputComponent->BindAxis("MoveX" , this, &AAPM_PacMan::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &AAPM_PacMan::MoveY);

	//Overlap
	this->OnActorBeginOverlap.AddDynamic(this, &AAPM_PacMan::OnOverlap);

}

void AAPM_PacMan::MoveX(float Value)
{
    InputX = Value;  // Stocker l'input sur l'axe X
    FVector Direction = FVector(1, 0, 0);
    AddActorWorldOffset(Direction * Value * GetWorld()->GetDeltaSeconds() * Speed, true);

    Rotate();  // Appeler Rotate après le déplacement
}

void AAPM_PacMan::MoveY(float Value)
{
    InputY = Value;  // Stocker l'input sur l'axe Y
    FVector Direction = FVector(0, 1, 0);
    AddActorWorldOffset(Direction * Value * GetWorld()->GetDeltaSeconds() * Speed, true);

    Rotate();  // Appeler Rotate après le déplacement
}

void AAPM_PacMan::Rotate()
{
	// Si aucun input n'est donné, ne pas tourner
	if (FMath::IsNearlyZero(InputX) && FMath::IsNearlyZero(InputY))
	{
		return;
	}

	// Créer un vecteur basé sur les inputs
	FVector MovementDirection = FVector(InputX, InputY, 0).GetSafeNormal();  // Normaliser le vecteur

	// Convertir la direction en une rotation, en conservant l'axe X d'origine
	FRotator TargetRotation = MovementDirection.Rotation();

	// Comme ton mesh a une rotation de 90° sur l'axe X par défaut, on l'ajuste ici
	FRotator AdjustedRotation = FRotator(0, TargetRotation.Yaw - 90, 90.0f);

	// Appliquer la rotation seulement au mesh
	StaticMesh->SetWorldRotation(FMath::RInterpTo(StaticMesh->GetComponentRotation(), AdjustedRotation, GetWorld()->GetDeltaSeconds(), 10.0f));
}





void AAPM_PacMan::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	if(auto PacGum = Cast<AAPM_PacGum>(OtherActor))
	{
		if(PacGum->IsSuperGum)
		{
			if(MangeSuperPacGumSound)
			{
				UGameplayStatics::PlaySound2D(this, MangeSuperPacGumSound);
			}
			
			SuperPacMan();
			GameMode->SuperPacGumMange(PacGum);
		}
		else
		{
			if (MangePacGumSound1 && MangePacGumSound2)
			{
				if (!AudioComponent->IsPlaying())
				{
					if(MangePacGumSound)
					{
						AudioComponent->SetSound(MangePacGumSound2);
						MangePacGumSound = false;
					}
					else
					{
						AudioComponent->SetSound(MangePacGumSound1);
						MangePacGumSound = true;
					}
					AudioComponent->Play();
				}
			}
			
			GameMode->PacGumMange(PacGum);
		}

		PacGum->Destroy();
	}
	else if(auto Ghost = Cast<AAPM_Ghost>(OtherActor))
	{
		auto GhostAIController = Cast<AAPM_GhostAIController>(Cast<AAPM_Ghost>(Ghost)->GetController());
		
		if(GhostAIController && !GhostAIController->BlackboardComponent->GetValueAsBool("IsChasing"))
		{
			
			if(!GhostAIController->BlackboardComponent->GetValueAsBool("IsDead"))
			{
				if(MangeFantomeSound)
				{
					UGameplayStatics::PlaySound2D(this, MangeFantomeSound);
				}

				//Mort Fantome
				GhostAIController->BlackboardComponent->SetValueAsBool("IsDead", true);
				
				GameMode->FantomeMange();
			}
		}
		else
		{
			if(MortSound)
			{
				UGameplayStatics::PlaySound2D(this, MortSound);
			}
			
			GameMode->PacmanMort();
		}
	}
}

void AAPM_PacMan::SuperPacMan()
{
	TArray<AActor*> Ghosts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAPM_Ghost::StaticClass(), Ghosts);
	for(auto Actor : Ghosts)
	{
		if(auto Ghost = Cast<AAPM_Ghost>(Actor))
		{
			auto GhostAIController = Cast<AAPM_GhostAIController>(Ghost->GetController());
			if(GhostAIController && !GhostAIController->BlackboardComponent->GetValueAsBool("IsDead"))
			{
				GhostAIController->BlackboardComponent->SetValueAsBool("IsChasing", false);
				GhostAIController->BlackboardComponent->SetValueAsBool("IsFleeing", true);
			}
		}
	}
	
	if(!IsSuperPacMan)
	{
		IsSuperPacMan = true;
		Speed *= SpeedMultiplierSuperPacMan;
		GetWorld()->GetTimerManager().SetTimer(SuperPacManTimerHandle, this, &AAPM_PacMan::SuperPacManEnd, SuperPacManTime, false);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(SuperPacManTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(SuperPacManTimerHandle, this, &AAPM_PacMan::SuperPacManEnd, SuperPacManTime, false);
	}
}

void AAPM_PacMan::SuperPacManEnd()
{
	if(FinSuperPacGumSound)
	{
		UGameplayStatics::PlaySound2D(this, FinSuperPacGumSound);
	}
	
	//Chasse Fantomes
	TArray<AActor*> Ghosts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAPM_Ghost::StaticClass(), Ghosts);
	for(auto Ghost : Ghosts)
	{
		auto GhostAIController = Cast<AAPM_GhostAIController>(Cast<AAPM_Ghost>(Ghost)->GetController());
		if(GhostAIController)
		{
			if(!GhostAIController->BlackboardComponent->GetValueAsBool("IsDead"))
			{
				GhostAIController->BlackboardComponent->SetValueAsBool("IsChasing", true);
				GhostAIController->BlackboardComponent->SetValueAsBool("IsFleeing", false);
			}
		}
	}

	
	IsSuperPacMan = false;
	Speed /= SpeedMultiplierSuperPacMan;
	GetWorld()->GetTimerManager().ClearTimer(SuperPacManTimerHandle);
	GameMode->ResetMultiplicateur();
}

void AAPM_PacMan::ResetLocation()
{
	SetActorLocation(StartLocation);

	if(IsSuperPacMan)
	{
		IsSuperPacMan = false;
		Speed /= SpeedMultiplierSuperPacMan;
		GetWorld()->GetTimerManager().ClearTimer(SuperPacManTimerHandle);
		GameMode->ResetMultiplicateur();
	}
}