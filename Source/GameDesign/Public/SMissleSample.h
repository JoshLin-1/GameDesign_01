// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGamePlayInterface.h"
#include "GameFramework/Actor.h"
#include "SMissleSample.generated.h"


class ARTSHUD; 

UCLASS()
class GAMEDESIGN_API ASMissleSample : public AActor, public ISGamePlayInterface
{
	GENERATED_BODY()

	void InteractToMousePosition_Implementation(FVector CursorPosition) override;
	void RightMouseInteract_Implementation() override;
	void MouseWhellInteract_Implementation(float Value) override;

	
public:	
	// Sets default values for this actor's properties
	ASMissleSample();

	/** Returns CursorToWorld subobject**/
	FORCEINLINE class UDecalComponent* GetCursorToWorld(){return CursorToWorld;}

	void SetSelected();
	void SetDeSelected();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta=(AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld; 
};
