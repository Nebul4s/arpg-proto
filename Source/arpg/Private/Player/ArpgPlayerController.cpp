// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ArpgPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Input/ArpgInputComponent.h"
#include "Interaction/EnemyInterface.h"

AArpgPlayerController::AArpgPlayerController()
{
	bReplicates = true;
}

void AArpgPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	
}

void AArpgPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = CurrentActor;
	CurrentActor = CursorHit.GetActor();

	if (LastActor != CurrentActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (CurrentActor) CurrentActor->HighlightActor();
	}
}

void AArpgPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}

void AArpgPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Red, *InputTag.ToString());
}

void AArpgPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Red, *InputTag.ToString());
}


void AArpgPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(ArpgContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(ArpgContext, 0);
	};

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AArpgPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UArpgInputComponent* ArpgInputComponent = CastChecked<UArpgInputComponent>(InputComponent);
	ArpgInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AArpgPlayerController::Move);
	ArpgInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AArpgPlayerController::Move(const struct FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

