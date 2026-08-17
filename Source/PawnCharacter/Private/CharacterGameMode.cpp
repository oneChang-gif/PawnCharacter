#include "CharacterGameMode.h"
#include "MyPawn.h"
#include "PawnController.h"

ACharacterGameMode::ACharacterGameMode()
{
    DefaultPawnClass = AMyPawn::StaticClass();
    PlayerControllerClass = APawnController::StaticClass();
}