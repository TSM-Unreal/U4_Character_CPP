// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Shinbi_Player.h"

// Sets default values
AShinbi_Player::AShinbi_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = SpringArmLengthMax;
	SpringArm->bUsePawnControlRotation = true;
	Camera1 = CreateDefaultSubobject<UCameraComponent>("Camera1");
	Camera1->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	bInFirstPerson = false;
}

// Called when the game starts or when spawned
void AShinbi_Player::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShinbi_Player::PostInitializeComponents()
{
	Super::PostInitializeComponents();
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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AShinbi_Player::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AShinbi_Player::StopJumping);
	PlayerInputComponent->BindAction("ToggleView", IE_Pressed, this, &AShinbi_Player::ToggleView);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShinbi_Player::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShinbi_Player::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);
}

void AShinbi_Player::ToggleView()
{
	bInFirstPerson = !bInFirstPerson;
	auto PlayerController = GetController<APlayerController>();
	if (!PlayerController) { return; }

	if (bInFirstPerson)
	{
		SpringArm->TargetArmLength = SpringArmLengthMin;
		SpringArm->AttachTo(GetMesh(), "Head_Camera");

	}
	else
	{
		SpringArm->AttachTo(RootComponent);
		SpringArm->TargetArmLength = SpringArmLengthMax;

	}
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
	GetCharacterMovement()->MaxWalkSpeed = 900.f;
}

void AShinbi_Player::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void AShinbi_Player::BlowKiss()
{
	if (BlowKissAnimation)
	{
		GLog->Log(TEXT("Blow Kiss"));

		PlayAnimMontage(BlowKissAnimation);

	}
}

