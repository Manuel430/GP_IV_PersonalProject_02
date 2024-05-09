// Fill out your copyright notice in the Description page of Project Settings.

#include "GPIV_PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"


AGPIV_PlayerCharacter::AGPIV_PlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	ViewCamera = CreateDefaultSubobject<UCameraComponent>("View Camera");
	SamusMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Samus Mesh");

	CameraBoom->SetupAttachment(GetRootComponent());
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SamusMeshComponent->SetupAttachment(ViewCamera);

	CameraBoom->bUsePawnControlRotation = true;

	GetCharacterMovement()->JumpZVelocity = 600.f;
	JumpMaxCount = 2;

}

void AGPIV_PlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		InputSubsystem->AddMappingContext(InputMapping, 0);
	}
}

void AGPIV_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComp)
	{
		EnhancedInputComp->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::Move);
		EnhancedInputComp->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::Look);
		EnhancedInputComp->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::JumpAction);
		EnhancedInputComp->BindAction(MorphballInputAction, ETriggerEvent::Triggered, this, &AGPIV_PlayerCharacter::Morphball);
	}
}

void AGPIV_PlayerCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2D Input = InputValue.Get<FVector2D>();
	Input.Normalize();

	if (bIsMorphballMode)
	{
		AddMovementInput(Input.Y * GetMoveFwdDir());
	}
	else
	{
		AddMovementInput(Input.Y * GetMoveFwdDir() + Input.X * GetMoveRightDir());
	}
}

void AGPIV_PlayerCharacter::Look(const FInputActionValue& InputValue)
{
	FVector2D Input = InputValue.Get<FVector2D>();
	AddControllerYawInput(Input.X);
	AddControllerPitchInput(-Input.Y);
}

void AGPIV_PlayerCharacter::JumpAction(const FInputActionValue& InputValue)
{
	Jump();
}

void AGPIV_PlayerCharacter::Morphball(const FInputActionValue& InputValue)
{
	if (bIsMorphballMode)
	{
		CameraBoom->TargetArmLength = 0;
		GetCharacterMovement()->MaxWalkSpeed = 600;
		GetCapsuleComponent()->SetCapsuleHalfHeight(88);
		
		if (bCanDoubleJump)
		{
			JumpMaxCount = 2;
		}

		SamusMeshComponent->SetVisibility(true);
		GetMesh()->SetVisibility(false);

		//UE_LOG(LogTemp, Error, TEXT("Player is in Suit form"));
	}
	else
	{
		CameraBoom->TargetArmLength = 500;
		GetCharacterMovement()->MaxWalkSpeed = 6000;
		GetCapsuleComponent()->SetCapsuleHalfHeight(34);
		JumpMaxCount = 1;

		SamusMeshComponent->SetVisibility(false);
		GetMesh()->SetVisibility(true);

		//UE_LOG(LogTemp, Error, TEXT("Player is in Morphball form"));
	}

	bIsMorphballMode = !bIsMorphballMode;
}

void AGPIV_PlayerCharacter::Sprinting(const FInputActionValue& InputValue)
{
}

void AGPIV_PlayerCharacter::Walking(const FInputActionValue& InputValue)
{
}

void AGPIV_PlayerCharacter::Shooting(const FInputActionValue& InputValue)
{
}

FVector AGPIV_PlayerCharacter::GetMoveFwdDir() const
{
	FVector CameraFwd = ViewCamera->GetForwardVector();
	CameraFwd.Z = 0;
	return CameraFwd.GetSafeNormal();
}

FVector AGPIV_PlayerCharacter::GetMoveRightDir() const
{
	return ViewCamera->GetRightVector();
}

void AGPIV_PlayerCharacter::AllowDoubleJump()
{
	bCanDoubleJump = true;

	if (bIsMorphballMode)
	{
		return;
	}

	JumpMaxCount = 2;
}
