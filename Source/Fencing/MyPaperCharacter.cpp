// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPaperCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Engine/AssetManager.h"

AMyPaperCharacter::AMyPaperCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->SetupAttachment(RootComponent);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Flipbook);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(SpringArm);
	SpringArm->SetRelativeRotation(FRotator(0, -90, 0));
}
void AMyPaperCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateWalkAnimation();
}

void AMyPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//TObjectPtr<APlayerController>PlayerController = Cast<APlayerController>(GetController());
	//TObjectPtr<UEnhancedInputLocalPlayerSubsystem>InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	//InputLocalPlayerSubsystem->AddMappingContext(InputMapping, 0);
	//TObjectPtr<UEnhancedInputComponent> PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	//if (EnhancedInputComponent) {
	//	EnhancedInputComponent->
	//}
	// PlayerEnhancedInputComponent->BindAxis("MoveRight",this, &AMyPaperCharacter::MoveRight);
}

bool AMyPaperCharacter::UpdateWalkAnimation_Implementation()
{
	bool IsWalking;
	if (GetCharacterMovement()->Velocity.Size() > 0) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Velocity: %f cm/s"), GetCharacterMovement()->Velocity.Size()));
		IsWalking = true;
		//static const FString RunAssetPath = TEXT("/Script/Paper2D.PaperFlipbook'/Game/Flipbook/Warrior_Run.Warrior_Run'");
		TObjectPtr<UPaperFlipbook> RunAnim = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Script/Paper2D.PaperFlipbook'/Game/Flipbook/Warrior_Run.Warrior_Run'"));
		Flipbook->SetFlipbook(RunAnim);
		
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Velocity: %f cm/s"), GetCharacterMovement()->Velocity.Size()));
		IsWalking = false;
		//static const FString IdleAssetPath = TEXT("/Script/Paper2D.PaperFlipbook'/Game/Flipbook/Warrior_Idle.Warrior_Idle'");
		TObjectPtr<UPaperFlipbook> IdleAnim = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Script/Paper2D.PaperFlipbook'/Game/Flipbook/Warrior_Idle.Warrior_Idle'"));
		//static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleAnimAsset(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Flipbook/Warrior_Run.Warrior_Run'"));
		Flipbook->SetFlipbook(IdleAnim);
	}
	return IsWalking;
}

//void AMyPaperCharacter::MoveRight(float InputValue) {
//	FVector RightDirection = GetActorRightVector();
//	AddMovementInput(RightDirection,InputValue);
//}


