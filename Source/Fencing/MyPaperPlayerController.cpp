// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPaperPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyPaperCharacter.h"
#include "MyPaperPlayerController.h"
//#include "Components/InputComponent.h"
//#include "GameFramework/PlayerController.h"
//#include "GameFramework/Controller.h"
//#include "GameFramework/Pawn.h"

void AMyPaperPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	TObjectPtr<UEnhancedInputComponent>EnhancedInputComponent = Cast<UEnhancedInputComponent>(this->InputComponent);
	//InputComponent->BindAxis("ActionMove", this, &AMyPaperPlayerController::Move);
	EnhancedInputComponent->BindAction(ActionMove.Get(),ETriggerEvent::Triggered, this, &AMyPaperPlayerController::Move);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Move!"));
}

void AMyPaperPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	this->CurrentCharacter = Cast<AMyPaperCharacter>(InPawn);
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem>InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());
	if (InputLocalPlayerSubsystem) {
		InputLocalPlayerSubsystem->AddMappingContext(this->CurrentMappingContext.Get(), 0);
	}
}

void AMyPaperPlayerController::Move(const FInputActionValue& Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Calisti!"));
	FVector MovementVector = Value.Get<FVector>();
	FVector RightVector = FVector::XAxisVector;
	CurrentCharacter->AddMovementInput(RightVector, MovementVector.X);
	//CurrentCharacter->AddMovementInput(RightVector, MovementVector.Y);
	//CurrentCharacter->AddMovementInput(RightVector, MovementVector.Z);
}

//void AMyPaperPlayerController::Move(float Value)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Calisti!"));
//	FVector RightVector = FVector::RightVector;
//	CurrentCharacter->AddMovementInput(RightVector, Value);
//}
