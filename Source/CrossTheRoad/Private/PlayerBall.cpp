// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBall.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
//#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "TimerManager.h"


// Sets default values
APlayerBall::APlayerBall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Collision root component (Text - Default Name)
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;
	// Set the sphere radius (Float value)
	Collision->InitSphereRadius(50.f);

	// Mesh attachement to the sphere (Text - Default Name)
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);

	// Camera attachement to the spring arm (Text - Default Name)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	// Set the spring arm length (Float value)
	SpringArm->TargetArmLength = 800.f;
	// Allow the spring arm to rotate ()
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	// Camera placement (Text - Default Name)
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	//// Pawn movement component (Text - Default Name)
	//MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

	// Give the ability to player to control
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APlayerBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//check(PlayerInputComponent);

	UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent CALLED!"));

	if (PlayerInputComponent) {
		//BindAxis("InputName", UserClass, &Function)
		PlayerInputComponent->BindAction("MoveForward", IE_Pressed, this, &APlayerBall::MoveForward);
		PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &APlayerBall::MoveRight);
		PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &APlayerBall::MoveLeft);
	}
}

void APlayerBall::ResetStep() {
	bCanStep = true;
}

void APlayerBall::MoveForward() {
	
	if (!bCanStep) return;
	bCanStep = false;

	// Move the ball forward by StepSize units
	FVector Step = FVector(StepSize, 0.f, 0.f);
	
	// Setting the actor location directly to avoid physics issues
	SetActorLocation(GetActorLocation() + Step, true);

	// Start the cooldown timer
	GetWorldTimerManager().SetTimer(StepTimer, this, &APlayerBall::ResetStep, StepCooldown, false);
	
	UE_LOG(LogTemp, Warning, TEXT("Move Forward: %f"), StepSize);
	
	//if (value != 0.f) {
	//	FVector Step = FVector(value * StepSize, 0.f, 0.f);
	//	AddActorWorldOffset(Step, true);
	//	//AddMovementInput(FVector::ForwardVector, value);
	//	UE_LOG(LogTemp, Warning, TEXT("Move Forward"), value);
	//}
}


void APlayerBall::MoveRight() {
	
	if (!bCanStep) return;
	bCanStep = false;

	// Move the ball forward by StepSize units
	FVector Step = FVector(0.f, StepSize, 0.f);

	// Setting the actor location directly to avoid physics issues
	SetActorLocation(GetActorLocation() + Step, true);

	// Start the cooldown timer
	GetWorldTimerManager().SetTimer(StepTimer, this, &APlayerBall::ResetStep, StepCooldown, false);

	UE_LOG(LogTemp, Warning, TEXT("Move Right: %f"), StepSize);
}

void APlayerBall::MoveLeft() {

	if (!bCanStep) return;
	bCanStep = false;

	// Move the ball forward by StepSize units
	FVector Step = FVector(0.f, -StepSize, 0.f);

	// Setting the actor location directly to avoid physics issues
	SetActorLocation(GetActorLocation() + Step, true);

	// Start the cooldown timer
	GetWorldTimerManager().SetTimer(StepTimer, this, &APlayerBall::ResetStep, StepCooldown, false);

	UE_LOG(LogTemp, Warning, TEXT("Move Left: %f"), StepSize);
}