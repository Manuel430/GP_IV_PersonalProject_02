// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GPIV_EndGameWidget.h"
#include "GPIV_EndGameWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGPIV_EndGameWidget::NativeConstruct()
{
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UGPIV_EndGameWidget::OnQuitClick);
	}
}

void UGPIV_EndGameWidget::OnQuitClick()
{
	APlayerController* SpecificPlayer = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), SpecificPlayer, EQuitPreference::Quit, true);
}
