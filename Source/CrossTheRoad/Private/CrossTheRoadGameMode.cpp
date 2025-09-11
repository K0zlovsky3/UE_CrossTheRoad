// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossTheRoadGameMode.h"

ACrossTheRoadGameMode::ACrossTheRoadGameMode() : Super()
{
	ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/Blueprints/BP_PlayerBall"));

	DefaultPawnClass = PlayerPawn.Class;
}
