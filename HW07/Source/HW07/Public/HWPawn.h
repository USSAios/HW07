// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "HWPawn.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class HW07_API AHWPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHWPawn();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision");
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StaticMesh");
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float SavedDeltaTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Speed")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Speed")
	float AscentSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Speed")
	float G;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Speed")
	float RollSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Speed")
	float AirSpeed;

	bool IsFlying;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void Flight(const FInputActionValue& value);
	UFUNCTION()
	void Roll(const FInputActionValue& value);
	
	UFUNCTION()
	void ApplyGravity();

	UFUNCTION()
	bool IsHitGround();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* FlightAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* RollAction;



};
