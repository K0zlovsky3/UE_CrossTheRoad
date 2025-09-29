// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBall.h"
#include "Car.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "TimerManager.h"
#include "CrossTheRoadGameMode.h"
#include "Kismet/GameplayStatics.h"


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

	// Give the ability to player to control
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APlayerBall::BeginPlay()
{
	Super::BeginPlay();

	// Start to check for overlaps
	Collision->OnComponentBeginOverlap.AddDynamic(this, &APlayerBall::OnOverlapBegin);
	
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
	
	// check if can step or is alive
	if (!bCanStep || !bIsAlive) return;
	bCanStep = false;

	// Move the ball forward by StepSize units
	FVector Step = FVector(StepSize, 0.f, 0.f);
	
	// Setting the actor location directly to avoid physics issues
	SetActorLocation(GetActorLocation() + Step, true);

	// Start the cooldown timer
	GetWorldTimerManager().SetTimer(StepTimer, this, &APlayerBall::ResetStep, StepCooldown, false);
	
	UE_LOG(LogTemp, Warning, TEXT("Move Forward: %f"), StepSize);
}

void APlayerBall::MoveRight() {
	
	// check if can step or is alive
	if (!bCanStep || !bIsAlive) return;
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

	// check if can step or is alive
	if (!bCanStep || !bIsAlive) return;
	bCanStep = false;

	// Move the ball forward by StepSize units
	FVector Step = FVector(0.f, -StepSize, 0.f);

	// Setting the actor location directly to avoid physics issues
	SetActorLocation(GetActorLocation() + Step, true);

	// Start the cooldown timer
	GetWorldTimerManager().SetTimer(StepTimer, this, &APlayerBall::ResetStep, StepCooldown, false);

	UE_LOG(LogTemp, Warning, TEXT("Move Left: %f"), StepSize);
}

void APlayerBall::OnOverlapBegin(
	class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
) {
	// Check if the overlapping actor is valid and not itself
	if (OtherActor && OtherActor != this) {
		if (OtherActor->IsA(ACar::StaticClass())) {
			UE_LOG(LogTemp, Warning, TEXT("Overlap Begin with %s"), *OtherActor->GetName());
			DeathEvent();
		}
	}
}

void APlayerBall::DeathEvent() {
	// Handle game over logic here (e.g., disable input, play animation, etc.)
	if (!bIsAlive) return;
	bIsAlive = false;

	UE_LOG(LogTemp, Warning, TEXT("Player has died. Game Over."));

	// Notify the game mode about the game over
	ACrossTheRoadGameMode* GameMode = Cast<ACrossTheRoadGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode) {
		GameMode->GameOver();
	}
}