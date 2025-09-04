// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPaperCharacter.h"
#include "MyPaperPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
class ACharacterBase;

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class FENCING_API AMyPaperPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> CurrentMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> ActionMove;

	TObjectPtr<AMyPaperCharacter> CurrentCharacter;

	virtual void SetupInputComponent() override;
protected:
	virtual void OnPossess(APawn* InPawn) override;

	//void Move(float Value);

	void Move(const FInputActionValue& Value);
};
