// Copyright Patrick Carvalho All Rights Reserved.
// sysware@sysware.com.br
// 

#include "MyPathPlayerController.h"

AMyPathPlayerController::AMyPathPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

