// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHUD.generated.h"


/**
 * 
 */

class ASMissleSample;

UCLASS()
class GAMEDESIGN_API ARTSHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void DrawHUD() override; //same as tick
	
	FVector2D InitialPoint; // Position of mouse on screen when presse
	FVector2D CurrentPoint; // Position of mouse on screen when release

	FVector2D GetMousePos2D();
	
	UPROPERTY(BlueprintReadOnly)
	bool bStartSelecting = false;

	UPROPERTY()
	TArray<ASMissleSample*> FoundActors; 
};
