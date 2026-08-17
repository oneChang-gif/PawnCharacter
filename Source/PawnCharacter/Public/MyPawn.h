#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UCapsuleComponent;
class UArrowComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;

struct FInputActionValue;

UCLASS()
class PAWNCHARACTER_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyPawn();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* SkeletalMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotationSpeed;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
};
