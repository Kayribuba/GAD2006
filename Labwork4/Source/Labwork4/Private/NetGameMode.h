// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetAvatar.h"
#include "NetGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ANetGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ANetGameMode();

	virtual void BeginPlay() override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	UFUNCTION(BlueprintCallable)
		void AvatarsOverlapped(ANetAvatar* AvatarA, ANetAvatar* AvatarB);

	UFUNCTION(BlueprintCallable)
		void EndGame();

	UFUNCTION(BlueprintCallable)
		void RestartTimeFunction();

private:
	int TotalPlayerCount;
	int TotalGames;
	int PlayerStartIndex;
	int TimeRemaining;
	int GameLenght;

	void TimeFunction();

	TArray<APlayerController*> AllPlayers;

	AActor* GetPlayerStart(FString Name, int Index);

	AActor* AssignTeamAndPlayerStart(AController* Player);


	FTimerHandle TimeTimer;
};
