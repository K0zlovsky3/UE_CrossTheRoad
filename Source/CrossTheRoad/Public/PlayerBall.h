// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerBall.generated.h"

UCLASS()
class CROSSTHEROAD_API APlayerBall : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerBall();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Reset the ability to step
	void ResetStep();

	void DeathEvent();

	// Overlap event
	UFUNCTION()
	void OnOverlapBegin(
		class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	
	// Ball movement
	void MoveForward();
	void MoveRight();
	void MoveLeft();

	// Ball collision component
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Collision;

	// Ball mesh component
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	// Spring arm component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USpringArmComponent* SpringArm;

	// Camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* Camera;

	// Step size for each movement input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StepSize = 200.f;

	// Cooldown time between steps
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StepCooldown = 0.2f;

	// bool to check if the player can step
	bool bCanStep = true;

	// bool to check if the player is alive
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsAlive = true;

	FTimerHandle StepTimer;
};
