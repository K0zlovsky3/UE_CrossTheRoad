// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoadWay.generated.h"

UCLASS()
class CROSSTHEROAD_API ARoadWay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoadWay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* RoadMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic")
	TSubclassOf<AActor> CarClass;

	// Time interval between car spawns
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic")
	float SpawnInterval = 2.f;

	// Speed of spawned cars
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic")
	float CarSpeed = 200.f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic")
	//int32 Direction = 1; // 1 for forward, -1 for backward

	// Spawn location for cars
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic")
	FVector SpawnOffset;

private:
	FTimerHandle SpawnTimer;
	
	void SpawnCar();
};
