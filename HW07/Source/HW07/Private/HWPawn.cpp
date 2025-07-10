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
	AscentSpeed = 300.f;
	G = 150.0f;
	RollSpeed = 30.0f;
	AirSpeed = 0.6f;
	IsFlying = false;
}

// Called when the game starts or when spawned
void AHWPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHWPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SavedDeltaTime = DeltaTime;

	ApplyGravity();

}

// Called to bind functionality to input
void AHWPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if(PlayerController)
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

				EnhancedInput->BindAction(
					FlightAction,
					ETriggerEvent::Triggered,
					this,
					&AHWPawn::Flight
				);
				
				EnhancedInput->BindAction(
					RollAction,
					ETriggerEvent::Triggered,
					this,
					&AHWPawn::Roll
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
		if (IsFlying)
		{
			AddActorWorldOffset(GetActorForwardVector() * MoveVector.X * Speed * SavedDeltaTime * AirSpeed, true);
		}
		else
		{
			AddActorWorldOffset(GetActorForwardVector() * MoveVector.X * Speed * SavedDeltaTime, true);
		}
	}
	
	if (!FMath::IsNearlyZero(MoveVector.Y))
	{
		if (IsFlying)
		{
			AddActorWorldOffset(GetActorRightVector() * MoveVector.Y * Speed * SavedDeltaTime * AirSpeed, true);
		}
		else
		{
			AddActorWorldOffset(GetActorRightVector() * MoveVector.Y * Speed * SavedDeltaTime, true);
		}
	}

}

void AHWPawn::Look(const FInputActionValue& value)
{
	const FVector2D RotationVector = value.Get<FVector2D>();

	FRotator DeltaRotation = FRotator(RotationVector.Y, RotationVector.X, 0.0f);

	AddActorLocalRotation(DeltaRotation);
}

void AHWPawn::Flight(const FInputActionValue& value)
{
	FVector Ascentvector = value.Get<FVector>();

	if (!FMath::IsNearlyZero(Ascentvector.X))
	{
		AddActorLocalOffset(GetActorUpVector() * Ascentvector.X * AscentSpeed * SavedDeltaTime);
	}

	if (IsHitGround() == false && Ascentvector.X > 0)
	{
		IsFlying = true;
	}

}

void AHWPawn::Roll(const FInputActionValue& value)
{
	FVector Rollvector = value.Get<FVector>();

	if (!FMath::IsNearlyZero(Rollvector.X))
	{
		FRotator DeltaRotation = FRotator(0.0f, 0.0f, Rollvector.X * RollSpeed * SavedDeltaTime);

		AddActorLocalRotation(DeltaRotation);
	}
}

void AHWPawn::ApplyGravity()
{
	if (IsHitGround())
	{
		G = 0.0f;
		IsFlying = false;
	}
	else
	{
		G = 150.0f;
	}

	AddActorWorldOffset(FVector(0, 0, -G) * SavedDeltaTime, true);

}

bool AHWPawn::IsHitGround()
{
	FHitResult OutHit;
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorUpVector() * -60.0f;
	ECollisionChannel TraceChannel = ECC_WorldStatic;
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);

	bool HitResult = GetWorld()->LineTraceSingleByChannel(
		OutHit,
		Start,
		End,
		TraceChannel,
		Params
	);

	return HitResult;
}


