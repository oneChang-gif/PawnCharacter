#include "MyPawn.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "UObject/ConstructorHelpers.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "PawnController.h"

AMyPawn::AMyPawn()
{

	PrimaryActorTick.bCanEverTick = false;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	RootComponent = CapsuleComp;
	CapsuleComp->SetSimulatePhysics(false);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(RootComponent);
	SkeletalMeshComp->SetSimulatePhysics(false);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Resources/Characters/Meshes/SKM_Manny.SKM_Manny"));
	if (MeshAsset.Succeeded())
	{
		SkeletalMeshComp->SetSkeletalMesh(MeshAsset.Object);
		SkeletalMeshComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	}
	MoveSpeed = 600.0f;
	RotationSpeed = 100.0f;
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APawnController* PawnController = Cast<APawnController>(GetController()))
		{
			if (PawnController->MoveAction)
			{
				EnhancedInput->BindAction(PawnController->MoveAction, ETriggerEvent::Triggered, this, &AMyPawn::Move);
			}

			if (PawnController->LookAction)
			{
				EnhancedInput->BindAction(PawnController->LookAction, ETriggerEvent::Triggered, this, &AMyPawn::Look);
			}
		}
	}
}

void AMyPawn::Move(const FInputActionValue& value)
{
	const FVector2D MoveInput = value.Get<FVector2D>();
	if (MoveInput.IsNearlyZero()) return;

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	FVector DeltaLocation = FVector(MoveInput.X, MoveInput.Y, 0.0f) * MoveSpeed * DeltaTime;

	AddActorLocalOffset(DeltaLocation, true);
}

void AMyPawn::Look(const FInputActionValue& value)
{
	const FVector2D LookInput = value.Get<FVector2D>();
	if (LookInput.IsNearlyZero()) return;

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	FRotator DeltaRotation = FRotator(LookInput.Y * RotationSpeed * DeltaTime, LookInput.X * RotationSpeed * DeltaTime, 0.0f);

	AddActorLocalRotation(DeltaRotation);
}


