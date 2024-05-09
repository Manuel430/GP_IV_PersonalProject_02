// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPIV_MissileDestructible.generated.h"

class UStaticMeshComponent;

UCLASS()
class AGPIV_MissileDestructible : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ObjectMesh;

	// Sets default values for this actor's properties
	AGPIV_MissileDestructible();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
