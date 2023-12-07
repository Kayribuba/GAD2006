// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "COA_BaseCharacter.generated.h"

UCLASS()
class ACOA_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACOA_BaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float HealRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float WalkingSpeed;

	UPROPERTY(VisibleAnywhere, Category = "COA")
		bool bDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		bool Update;

	UFUNCTION(BlueprintCallable, Category = "COA")
		void SetHealth(float NewHealth);

	UFUNCTION(BlueprintCallable, Category = "COA")
		float GetHealth();

	UFUNCTION(BlueprintNativeEvent, Category = "COA")
		float ModifyDamage(float incomingDamage);

	UFUNCTION(BlueprintImplementableEvent, Category = "COA")
		void OnPlayerDied();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
