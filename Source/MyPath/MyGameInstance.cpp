// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::MessageLog()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Game Instance OK !!")));
}


UMyGameInstance::UMyGameInstance()
{
	MessageLog();
}
