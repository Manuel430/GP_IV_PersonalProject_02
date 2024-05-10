// Fill out your copyright notice in the Description page of Project Settings.


#include "Ending/GPIV_EscapeCollision.h"
#include "Components/SphereComponent.h"
#include "Player/GPIV_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/GPIV_GameMode.h"

// Sets default values
AGPIV_EscapeCollision::AGPIV_EscapeCollision()
{
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SphereCollider->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	RootComponent = SphereCollider;
}

// Called when the game starts or when spawned
void AGPIV_EscapeCollision::BeginPlay()
{
	Super::BeginPlay();
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AGPIV_EscapeCollision::OnSphereOverlap);
}

void AGPIV_EscapeCollision::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGPIV_PlayerCharacter* PlayerCharacter = Cast<AGPIV_PlayerCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		AGPIV_GameMode* GameMode = GetWorld()->GetAuthGameMode<AGPIV_GameMode>();
		GameMode->GameEnd();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

