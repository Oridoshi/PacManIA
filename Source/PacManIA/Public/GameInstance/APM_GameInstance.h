// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "APM_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PACMANIA_API UAPM_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Game Data")
	int Score;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Game Data")
	int NbVieRestante;

	virtual void Init() override;
};
