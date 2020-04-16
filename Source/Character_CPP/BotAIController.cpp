// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/Engine.h"
#include "TimerManager.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BotAIController.h"

static FName NAME_ShouldWanderKey("ShouldWander");
static FName NAME_EnemyKey("Enemy");

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

		BlackboardComp->SetValueAsBool(NAME_ShouldWanderKey, true);
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

	GetWorldTimerManager().SetTimer(OnResumeTimerHandle, this, &ABotAIController::OnResume, 10.f, true, 1.f);

}

void ABotAIController::OnResume()
{
	if (BlackboardComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ABotAIController: Wandering..."));
		BlackboardComp->SetValueAsObject(NAME_EnemyKey,nullptr);
		BlackboardComp->SetValueAsBool(NAME_ShouldWanderKey, true);
	}
}

void ABotAIController::OnSeePawn(APawn* SensedPawn)
{
	if (BlackboardComp && SensedPawn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ABotAIController: I See You"));
		BlackboardComp->SetValueAsObject(NAME_EnemyKey, SensedPawn);
		BlackboardComp->SetValueAsBool(NAME_ShouldWanderKey, false);
		GetWorldTimerManager().ClearTimer(OnResumeTimerHandle);
		GetWorldTimerManager().SetTimer(OnResumeTimerHandle, this, &ABotAIController::OnResume, 10.f, false, 1.f);
	}
}
