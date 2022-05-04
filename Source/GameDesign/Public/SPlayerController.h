// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

/**
 * 
 */

class AActor;
class UUserWidget;

UCLASS()
class GAMEDESIGN_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Distance")
	float TraceDistance;

	// UPROPERTY()
	// UUserWidget* PauseMenuInstance; 
	
public:
	ASPlayerController();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void PrimaryInteract();

	UFUNCTION()
	virtual void SetupInputComponent() override;

	UFUNCTION()
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;

	UFUNCTION()
	void MoveForward(float Value)
	{
		if (Value > 0.5)
		{
			UE_LOG(LogTemp, Warning, TEXT("Controller_Forward"));
		}
		else if (Value < -0.5)
		{
			UE_LOG(LogTemp, Warning, TEXT("Controller_BackWard"));
		}
	}
	
};
