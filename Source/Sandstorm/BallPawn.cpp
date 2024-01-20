// Fill out your copyright notice in the Description page of Project Settings.


#include "BallPawn.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ABallPawn::ABallPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	jumping = false;

}

UStaticMeshComponent* ABallPawn::FindComponentByTag(const FName& Tag)
{
	TArray<UStaticMeshComponent*> MeshComponents;
	GetComponents<UStaticMeshComponent>(MeshComponents);

	for (UStaticMeshComponent* MeshComponent : MeshComponents)
	{
		if (MeshComponent->ComponentHasTag(Tag))
		{
			return MeshComponent;
		}
	}

	return nullptr;
}


// Called when the game starts or when spawned
void ABallPawn::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* playerCtrl = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCtrl->GetLocalPlayer());
		subsystem->ClearAllMappings();
		subsystem->AddMappingContext(MappingContext, 0);
	}

	SphereMesh = FindComponentByTag("Sphere");

}

// Called every frame
void ABallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (jumping)
	{
		Jump();
	}

}

// Called to bind functionality to input
void ABallPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* inputcomp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		inputcomp->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ABallPawn::OnMovement);
	}

	InputComponent->BindAction("Jump", IE_Pressed, this, &ABallPawn::CheckJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ABallPawn::CheckJump);
}

void ABallPawn::CheckJump()
{
	if (jumping)
	{
		jumping = false;
	}
	else
	{
		jumping = true;
	}
}


void ABallPawn::OnMovement(const FInputActionValue& value)
{
	FInputActionValue::Axis2D inputValue = value.Get<FInputActionValue::Axis2D>();
	SphereMesh->AddForce(FVector(inputValue.X, inputValue.Y, 0));
}
