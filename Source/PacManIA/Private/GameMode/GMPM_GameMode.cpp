// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GMPM_GameMode.h"

void AGMPM_GameMode::PacGumMange()
{
	Score += NbPointPacGum;
}

void AGMPM_GameMode::SuperPacGumMange()
{
	Score += NbPointSuperPacGum;
}

void AGMPM_GameMode::FantomeMange()
{
	Score += NbPointFantome * Multiplicateur;
	Multiplicateur += AugmentationMultiplicateur;
}

void AGMPM_GameMode::ResetMultiplicateur()
{
	Multiplicateur = 1;
}
