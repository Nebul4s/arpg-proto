// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ArpgAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AArpgAIController::AArpgAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
	check(Blackboard);
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorComponent");
	check(BehaviorComp);
}
