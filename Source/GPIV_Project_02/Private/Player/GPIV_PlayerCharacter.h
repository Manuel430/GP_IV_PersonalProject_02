// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GPIV_CharacterBase.h"
#include "GPIV_PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class USkeletalMeshComponent;
class USceneComponent;
/**
 * 
 */
UCLASS()
class AGPIV_PlayerCharacter : public AGPIV_CharacterBase
{
	GENERATED_BODY()

public:
	AGPIV_PlayerCharacter();

private:
	UPROPERTY(visibleAnywhere, Category = "View")
	USpringArmComponent* CameraBoom;

	UPROPERTY(visibleAnywhere, Category = "View")
	UCameraComponent* ViewCamera;

	/*			Meshes			*/
	UPROPERTY(EditDefaultsOnly, Category = "Meshes")
	USkeletalMeshComponent* SamusMeshComponent;

	virtual void PawnClientRestart() override;

	/*			Input			*/

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MorphballInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* SprintInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* WalkInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ShootInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* QuitInputAction;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& InputValue);

	UFUNCTION()
	void Look(const FInputActionValue& InputValue);

	UFUNCTION()
	void JumpAction(const FInputActionValue& InputValue);

	UFUNCTION()
	void Morphball(const FInputActionValue& InputValue);

	UFUNCTION()
	void Sprinting(const FInputActionValue& InputValue);

	UFUNCTION()
	void Walking(const FInputActionValue& InputValue);

	UFUNCTION()
	void Shooting(const FInputActionValue& InputValue);

	UFUNCTION()
	void Quitting(const FInputActionValue& InputValue);

	FVector GetMoveFwdDir() const;
	FVector GetMoveRightDir() const;

	/*			Morphball			*/

protected:

	bool bIsMorphBall;
	
	bool bCanMorphBall = false;

public:
	UFUNCTION()
	void AllowMorphBall();

	/*			Upgrades			*/
protected:

	bool bCanDoubleJump = false;

public:

	UFUNCTION()
	void AllowDoubleJump();

	/*			Shooting			*/
private:

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	USceneComponent* SpawnPointComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AGPIV_Projectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	FVector MuzzleOffset;	
};
