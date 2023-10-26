// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CoreMinimal.h"
#include "COA_BaseCharacter.h"
#include "COA_Avatar.generated.h"

 
UCLASS()
class ACOA_Avatar : public ACOA_BaseCharacter
{
	GENERATED_BODY()
	
public:

	ACOA_Avatar();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "COA")
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "COA")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float RunningSpeed;

	UPROPERTY(VisibleAnywhere)
		float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float StaminaGainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float StaminaDrainRate;

	UPROPERTY(VisibleAnywhere)
		bool bStaminaDrained;

	UPROPERTY(VisibleAnywhere)
		bool bRunning;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void RunPressed();
	void RunReleased();

	void UpdateMovementParams();
};
