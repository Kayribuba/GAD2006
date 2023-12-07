// Fill out your copyright notice in the Description page of Project Settings.


#include "COA_BaseCharacter.h"

// Sets default values
ACOA_BaseCharacter::ACOA_BaseCharacter() :
	Health(0.0f),
	MaxHealth(100.0f),
	HealRate(10.0f),
	WalkingSpeed(250.0f),
	bDead(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = MaxHealth;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ACOA_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}

void ACOA_BaseCharacter::OnConstruction(const FTransform& Transform)
{
	Update = false;
}

// Called every frame
void ACOA_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Health = FMath::Min(MaxHealth, Health + HealRate * DeltaTime);

	//GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking;
	//GEngine->AddOnScreenDebugMessage(0, 1, FColor::White, UEnum::GetValueAsString(GetCharacterMovement()->MovementMode));
}

void ACOA_BaseCharacter::SetHealth(float NewHealth)
{
	Health = NewHealth;
}

float ACOA_BaseCharacter::GetHealth()
{
	return Health;
}

float ACOA_BaseCharacter::ModifyDamage_Implementation(float incomingDamage)
{
	return incomingDamage;
}

float ACOA_BaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bDead) return 0.0f;
	Damage = ModifyDamage(Damage);
	Health -= Damage;
	GEngine->AddOnScreenDebugMessage(0,1,FColor::Red, FString::Printf(TEXT("Health : %f"), Health));
	if (Health <= 0.0f)
	{
		bDead = true;
		APlayerController* player = Cast<APlayerController>(GetController());
		if (player != nullptr)DisableInput(player);
		OnPlayerDied();
	}

	return Damage;
}
