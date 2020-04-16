// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BotAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTER_CPP_API ABotAIController : public AAIController
{
	GENERATED_BODY()

public:

	ABotAIController();

	UFUNCTION(BlueprintCallable)
	void OnSeePawn(APawn* SensedPawn);

	FORCEINLINE class UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp;  }

protected:

	virtual void OnPossess(APawn* InPawn) override;

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(EditDefaultsOnly)
	class UBlackboardComponent* BlackboardComp;

	
};
