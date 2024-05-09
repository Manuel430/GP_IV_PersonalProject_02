// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/GPIV_MorphBallItem.h"
#include "Components/SphereComponent.h"
#include "Player/GPIV_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GPIV_MorphBallItem.h"


// Sets default values
AGPIV_MorphBallItem::AGPIV_MorphBallItem()
{
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SphereCollider->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	RootComponent = SphereCollider;

	UpgradeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Upgrade Mesh"));
	UpgradeMesh->SetupAttachment(SphereCollider);
	UpgradeMesh->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

// Called when the game starts or when spawned
void AGPIV_MorphBallItem::BeginPlay()
{
	Super::BeginPlay();
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AGPIV_MorphBallItem::OnSphereOverlap);
}

void AGPIV_MorphBallItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGPIV_PlayerCharacter* PlayerCharacter = Cast<AGPIV_PlayerCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		PlayerCharacter->AllowMorphBall();

		Destroy();
	}
}

