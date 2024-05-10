// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GPIV_EndGameWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class UGPIV_EndGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* QuitButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnQuitClick();
};
