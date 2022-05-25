// Fill out your copyright notice in the Description page of Project Settings.


#include "SPracticePlayerController.h"

#include "DrawDebugHelpers.h"
#include "NavigationSystem.h"
#include "SMissleSample.h"

ASPracticePlayerController::ASPracticePlayerController()
{
	bShowMouseCursor = true;
	// DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ASPracticePlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUDPtr = Cast<ARTSHUD>(GetHUD());
}

void ASPracticePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseClick",IE_Pressed, this, &ASPracticePlayerController::SelectionPressed);
	InputComponent->BindAction("LeftMouseClick",IE_Released, this, &ASPracticePlayerController::SelectionReleased);
	InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &ASPracticePlayerController::GetMouseLocation);
	InputComponent->BindAction("SelectActor", IE_Pressed, this, &ASPracticePlayerController::MoveReleased);
	InputComponent->BindAxis("MouseWheel", this, &ASPracticePlayerController::GetMouseWheelAxis);
}

void ASPracticePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASPracticePlayerController::SelectionPressed()
{
	HUDPtr->InitialPoint = HUDPtr->GetMousePos2D();
	HUDPtr->bStartSelecting = true;
}

void ASPracticePlayerController::SelectionReleased()
{
	HUDPtr->bStartSelecting = false;
	SelectedActors = HUDPtr->FoundActors;
}

void ASPracticePlayerController::MoveReleased()
{
	if(SelectedActors.Num()>0)
	{
		for(int i = 0; i<SelectedActors.Num(); i++)
		{
			ISGamePlayInterface::Execute_RightMouseInteract(SelectedActors[i]);
		}
	}
}

void ASPracticePlayerController::GetMouseLocation()
{
	// UE_LOG(LogTemp, Warning, TEXT("WorldLocation: %s"), *WorldLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Activate"));
	if(SelectedActors.Num()>0)
    	{
    		for(int i = 0; i<SelectedActors.Num(); i++)
    		{
    			FHitResult Hit;
    			GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
    			FVector MoveLocation = Hit.Location + FVector(i/2*100, i%2*100, 0);
    			// DrawDebugCircle(GetWorld(), MoveLocation, 100, 10, FColor::Blue, false, .3);
    			ISGamePlayInterface::Execute_InteractToMousePosition(SelectedActors[i], MoveLocation);
    			// UNavigationSystemV1::SimpleMoveToActor(SelectedActors[i]->GetInstigatorController(), MoveLocation);
    		}
    	}
}

void ASPracticePlayerController::GetMouseWheelAxis(float Value)
{
	if(SelectedActors.Num()>0)
	{
		for(int i = 0; i<SelectedActors.Num(); i++)
		{
			ISGamePlayInterface::Execute_MouseWhellInteract(SelectedActors[i], Value);
		}
	}
}


