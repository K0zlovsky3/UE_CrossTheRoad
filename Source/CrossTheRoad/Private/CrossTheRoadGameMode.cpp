// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossTheRoadGameMode.h"
#include "Kismet/GameplayStatics.h"

ACrossTheRoadGameMode::ACrossTheRoadGameMode() : Super()
{
	ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/Blueprints/BP_PlayerBall"));

	DefaultPawnClass = PlayerPawn.Class;
}

void ACrossTheRoadGameMode::GameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over!"));

	// Pause the game
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
