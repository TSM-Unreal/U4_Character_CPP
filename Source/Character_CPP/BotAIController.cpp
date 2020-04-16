// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/Engine.h"
#include "GameFramework/Pawn.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BotAIController.h"

ABotAIController::ABotAIController()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void ABotAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComp->StartTree(*BehaviorTree);

		BlackboardComp->SetValueAsBool(TEXT("ShouldWander"), true);
	}


}

void ABotAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}

void ABotAIController::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate fScriptDelegate;
	fScriptDelegate.BindUFunction(this, "OnSeePawn");
	PawnSensingComp->OnSeePawn.AddUnique(fScriptDelegate);

}

void ABotAIController::OnSeePawn(APawn* SensedPawn)
{
	if (BlackboardComp && SensedPawn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ABotAIController: I See You"));
		BlackboardComp->SetValueAsObject("Enemy", SensedPawn);
		BlackboardComp->SetValueAsBool("ShouldWander", false);
	}
}
