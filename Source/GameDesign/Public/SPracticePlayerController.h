// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSHUD.h"
#include "GameFramework/PlayerController.h"
#include "SPracticePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGN_API ASPracticePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASPracticePlayerController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	 
	virtual void Tick(float DeltaSeconds) override;

	
	ARTSHUD* HUDPtr;


protected:

	UFUNCTION()
	void SelectionPressed();

	UFUNCTION()
	void SelectionReleased();

	UFUNCTION()
	void MoveReleased();

	UFUNCTION()
	void GetMouseLocation();

	UFUNCTION()
	void GetMouseWheelAxis(float Value);

	UPROPERTY()
	TArray<ASMissleSample*> SelectedActors;
	

};
