// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Shinbi_Player.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class CHARACTER_CPP_API AShinbi_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShinbi_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera1;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float SpringArmLengthMax = 300.f;
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float SpringArmLengthMin = 0.f;

	bool bInFirstPerson;

	void ToggleView();

	void MoveForward(float Value);
	void MoveRight(float Value);
	void BeginSprint();
	void EndSprint();
	void BlowKiss();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* BlowKissAnimation;
};
