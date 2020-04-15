// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Shinbi_Player.h"

// Sets default values
AShinbi_Player::AShinbi_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bUsePawnControlRotation = true;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void AShinbi_Player::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShinbi_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShinbi_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AShinbi_Player::BeginSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AShinbi_Player::EndSprint);
	PlayerInputComponent->BindAction("BlowKiss", IE_Pressed, this, &AShinbi_Player::BlowKiss);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShinbi_Player::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShinbi_Player::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);
}

void AShinbi_Player::MoveForward(float Value)
{
	auto PlayerController = GetController<APlayerController>();
	if (PlayerController && Value != 0.f)
	{
		GLog->Log(TEXT("Forward"));
		FVector MoveDirection = GetActorForwardVector();
		AddMovementInput(MoveDirection, Value);
	}
}

void AShinbi_Player::MoveRight(float Value)
{
	auto PlayerController = GetController<APlayerController>();
	if (PlayerController && Value != 0.f)
	{
		GLog->Log(TEXT("Sideways"));
		FVector MoveDirection = GetActorRightVector();
		AddMovementInput(MoveDirection, Value);
	}
}

void AShinbi_Player::BeginSprint()
{
}

void AShinbi_Player::EndSprint()
{
}

void AShinbi_Player::BlowKiss()
{
	if (BlowKissAnimation)
	{
		GLog->Log(TEXT("Blow Kiss"));

		PlayAnimMontage(BlowKissAnimation);

	}
}

