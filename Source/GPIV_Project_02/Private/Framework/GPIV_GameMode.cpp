// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GPIV_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AGPIV_GameMode::BeginPlay()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
}

void AGPIV_GameMode::GameEnd()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	if (IsValid(EndGameWidget))
	{
		UUserWidget* Widget = CreateWidget(GetWorld(), EndGameWidget);
		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}
