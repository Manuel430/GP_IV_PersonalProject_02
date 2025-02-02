// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GPIV_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class AGPIV_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<UUserWidget> EndGameWidget;

	virtual void BeginPlay() override;

	UFUNCTION()
	void GameEnd();

};
