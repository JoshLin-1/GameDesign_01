// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSHUD.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

/**
 * 
 */

class ARTSHUD;
class AActor;
class ASMissleProjectileBase;

UCLASS()
class GAMEDESIGN_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Distance")
	float TraceDistance;

	void SelectionPressed();
	void SelectionReleased();
	void MoveReleased();

	UPROPERTY()
	TArray<ASMissleProjectileBase*> SelectedActors;

	FHitResult Hit; 

public:
	ASPlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	
	UFUNCTION()
	void PrimaryInteract();
	

	UFUNCTION()
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = "true") )
	FVector MouseLocation;

	UPROPERTY()
	ARTSHUD* HUDptr;
 
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
