// Fill out your copyright notice in the Description page of Project Settings.


#include "Destructible/GPIV_MissileDestructible.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGPIV_MissileDestructible::AGPIV_MissileDestructible()
{

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
	RootComponent = ObjectMesh;

}

// Called when the game starts or when spawned
void AGPIV_MissileDestructible::BeginPlay()
{
	Super::BeginPlay();
	
}

