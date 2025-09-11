// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "GameFramework/FloatingPawnMovement.h"
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

	//// Pawn movement component
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components");
	//class UFloatingPawnMovement* MovementComponent;

	// Step size for each movement input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StepSize = 200.f;

	// Cooldown time between steps
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StepCooldown = 0.2f;

	// bool to check if the player can step
	bool bCanStep = true;

	// Reset the ability to step
	void ResetStep();

	FTimerHandle StepTimer;
};
