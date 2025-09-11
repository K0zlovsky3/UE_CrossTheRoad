// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACar::ACar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Car mesh component (Text - Default Name)
	CarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarMesh"));
	CarMesh->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	UE_LOG(LogTemp, Warning, TEXT("Car spawned with MoveDirection: %s"), *MoveDirection.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Car BeginPlay at: %s"), *GetActorLocation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("StartLocation saved as: %s"), *StartLocation.ToString());
	
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move the car: NewLocation = CurrentLocation + Direction * Speed * DeltaTime
	FVector NewLocation = GetActorLocation() + MoveDirection * Speed * DeltaTime;
	SetActorLocation(NewLocation);

	// Check distance from start location
	float Distance = FVector::Dist(NewLocation, StartLocation);
	if (Distance > MaxDistance) {
		Destroy(); // Destroy the car if it has traveled beyond MaxDistance
	}
}

