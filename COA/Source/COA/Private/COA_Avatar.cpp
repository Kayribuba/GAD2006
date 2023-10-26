// Fill out your copyright notice in the Description page of Project Settings.


#include "COA_Avatar.h"


ACOA_Avatar::ACOA_Avatar() :
	RunningSpeed(500.0f),
	Stamina(0.0f),
	MaxStamina(100.0f),
	StaminaGainRate(50.0f),
	StaminaDrainRate(25.0f),
	bStaminaDrained(false),
	bRunning(false)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Stamina = MaxStamina;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	SpringArm->bUsePawnControlRotation = true;
	Camera->bUsePawnControlRotation = false;
}

void ACOA_Avatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStaminaDrained == false && bRunning)
	{
		Stamina = FMath::Max(0, Stamina - StaminaDrainRate * DeltaTime);
	}
	else if (Stamina < MaxStamina && GetCharacterMovement()->Velocity == FVector::ZeroVector)
	{
		Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime);
	}

	UpdateMovementParams();
	//GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking;
	//GEngine->AddOnScreenDebugMessage(0, 1, FColor::White, UEnum::GetValueAsString(GetCharacterMovement()->MovementMode));
}

// Called to bind functionality to input
void ACOA_Avatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACOA_Avatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACOA_Avatar::MoveRight);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACOA_Avatar::RunReleased);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACOA_Avatar::RunPressed);
}

void ACOA_Avatar::UpdateMovementParams()
{
	FString message = TEXT("");

	if (Stamina == 0)
	{
		bStaminaDrained = true;
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	}
	else if (Stamina == MaxStamina) { bStaminaDrained = false; }

	if (bStaminaDrained == false)
	{
		if (bRunning) { GetCharacterMovement()->MaxWalkSpeed = RunningSpeed; message = TEXT("Running. "); }
		else { GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed; message = TEXT("Walking. "); }
	}
	else { message = "Stamina Drained. "; }

	GEngine->AddOnScreenDebugMessage(0, 0.01f, FColor::White, FString::Printf(TEXT("%s Stamina left: %i"), *message, FMath::CeilToInt(Stamina)));
}

void ACOA_Avatar::MoveForward(float Amount)
{
	FRotator ControlRotation = GetControlRotation();
	FVector ForwardDirection = FRotationMatrix(FRotator(0.0f, ControlRotation.Yaw, 0.0f)).GetUnitAxis(EAxis::X);

	AddMovementInput(ForwardDirection, Amount);
}

void ACOA_Avatar::MoveRight(float Amount)
{
	FRotator ControlRotation = GetControlRotation();
	FVector RightDirection = FRotationMatrix(FRotator(0.0f, ControlRotation.Yaw, 0.0f)).GetUnitAxis(EAxis::Y);

	AddMovementInput(RightDirection, Amount);
}

void ACOA_Avatar::RunPressed() { bRunning = true; UpdateMovementParams(); }

void ACOA_Avatar::RunReleased() { bRunning = false; UpdateMovementParams(); }