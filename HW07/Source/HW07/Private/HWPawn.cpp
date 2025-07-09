// Fill out your copyright notice in the Description page of Project Settings.


#include "HWPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"

// Sets default values
AHWPawn::AHWPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(CapsuleComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(CapsuleComponent);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(CapsuleComponent);
	SpringArmComp->TargetArmLength = 500.0f;
	SpringArmComp->bUsePawnControlRotation = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	Speed = 600.0f;
}

// Called when the game starts or when spawned
void AHWPawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}

	}

	
}

// Called every frame
void AHWPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SavedDeltaTime = DeltaTime;

}

// Called to bind functionality to input
void AHWPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
		{
			if (MoveAction)
			{
				EnhancedInput->BindAction(
					MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AHWPawn::Move
				);

				EnhancedInput->BindAction(
					LookAction,
					ETriggerEvent::Triggered,
					this,
					&AHWPawn::Look
				);
				
			}
		}
	}
		
}

void AHWPawn::Move(const FInputActionValue& value)
{
	const FVector2D MoveVector = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveVector.X))
	{
		AddActorLocalOffset(GetActorForwardVector() * MoveVector.X * Speed * SavedDeltaTime);
	}
	
	if (!FMath::IsNearlyZero(MoveVector.Y))
	{
		AddActorLocalOffset(GetActorRightVector() * MoveVector.Y * Speed * SavedDeltaTime);
	}

}

void AHWPawn::Look(const FInputActionValue& value)
{
	const FVector2D RotationVector = value.Get<FVector2D>();


	FRotator DeltaRotation = FRotator(RotationVector.Y, RotationVector.X, 0.0f);

	AddActorWorldRotation(DeltaRotation);

	//AddActorLocalRotation(DeltaRotation);


}

