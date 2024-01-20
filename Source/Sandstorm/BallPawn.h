#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include <InputAction.h>
#include <InputMappingContext.h>
#include "BallPawn.generated.h"

UCLASS()
class SANDSTORM_API ABallPawn : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ABallPawn();

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UInputAction* MovementAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UInputMappingContext* MappingContext;

    UPROPERTY()
    bool jumping;

    UStaticMeshComponent* SphereMesh;

    UFUNCTION(BlueprintCallable, Category = "MyPawn")
    UStaticMeshComponent* FindComponentByTag(const FName& Tag);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void OnMovement(const FInputActionValue& value);

    void CheckJump();
};
