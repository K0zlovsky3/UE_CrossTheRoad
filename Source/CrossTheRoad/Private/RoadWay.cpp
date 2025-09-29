// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadWay.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
ARoadWay::ARoadWay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Road mesh component (Text - Default Name)
	RoadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoadMesh"));
	RootComponent = RoadMesh;
}

// Called when the game starts or when spawned
void ARoadWay::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("%s BeginPlay. ActorLoc=%s SpawnOffset=%s"), *GetName(), *GetActorLocation().ToString(), *SpawnOffset.ToString());
	// Start spawning cars at regular intervals
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ARoadWay::SpawnCar, SpawnInterval, true);


}

// Called every frame
void ARoadWay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoadWay::SpawnCar()
{
	if (!CarClass) return;

	FVector WorldSpawnLoc = RoadMesh->GetComponentLocation() + SpawnOffset;
	WorldSpawnLoc.Z += 50.f; // Adjust Z to be above the road

	UE_LOG(LogTemp, Warning, TEXT("Spawning car at %s (Actor %s, Offset %s)"), *WorldSpawnLoc.ToString(), *GetName(), *SpawnOffset.ToString());

	FActorSpawnParameters SpawnParams;
	AActor* Car = GetWorld()->SpawnActor<AActor>(CarClass, WorldSpawnLoc, FRotator::ZeroRotator, SpawnParams);
}

