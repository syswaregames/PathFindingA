// Copyright Patrick Carvalho All Rights Reserved.
// sysware@sysware.com.br
// 

#include "MyPathGameMode.h"
#include "MyPathPlayerController.h"
#include "MyPathPawn.h"

AMyPathGameMode::AMyPathGameMode()
{
	// no pawn by default
	DefaultPawnClass = AMyPathPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AMyPathPlayerController::StaticClass();
}
