// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGN_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Distance")
	float TraceDistance; 
	
public:
	ASPlayerController();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PrimaryInteract();

	virtual void SetupInputComponent() override;
};
