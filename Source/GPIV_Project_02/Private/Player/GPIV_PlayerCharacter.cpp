// Fill out your copyright notice in the Description page of Project Settings.

#include "GPIV_PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AGPIV_PlayerCharacter::AGPIV_PlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	ViewCamera = CreateDefaultSubobject<UCameraComponent>("View Camera");

	CameraBoom->SetupAttachment(GetRootComponent());
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	CameraBoom->bUsePawnControlRotation = true;

	GetCharacterMovement()->JumpZVelocity = 600.f;
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
	}
}

void AGPIV_PlayerCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2D Input = InputValue.Get<FVector2D>();
	Input.Normalize();

	AddMovementInput(Input.Y * GetMoveFwdDir() + Input.X * GetMoveRightDir());
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
