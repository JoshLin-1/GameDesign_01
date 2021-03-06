// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerController.h"
#include "DrawDebugHelpers.h"
#include "SGamePlayInterface.h"
#include "Camera/CameraActor.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


ASPlayerController::ASPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	// bEnableMouseOverEvents = false;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	// bAutoManageActiveCameraTarget = false;
	TraceDistance = 10000.f;

	
	
}

void ASPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUDptr = Cast<ARTSHUD>(GetHUD());
}

// void ASPlayerController::TogglePauseMenu()
// {
//
// 	if(PauseMenuInstance && PauseMenuInstance->IsInViewport())
// 	{
// 		PauseMenuInstance->RemoveFromParent();
// 		PauseMenuInstance = nullptr;
//
// 		// bShowMouseCursor = false;
// 		SetInputMode(FInputModeGameOnly());
// 		return; 
// 	}
// 	
// 	PauseMenuInstance = CreateWidget<UUserWidget>(this, PauseMenuClass);
// 	if(PauseMenuInstance)
// 	{
// 		PauseMenuInstance->AddToViewport(100);
//
// 		// bShowMouseCursor = true;
// 		SetInputMode(FInputModeUIOnly());
// 	}
// }

void ASPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// PrimaryInteract();

	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
	MouseLocation = Hit.Location;
	DrawDebugCircle(GetWorld(), MouseLocation, 32, 64, FColor::Blue);
}

void ASPlayerController::PrimaryInteract()
{

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();

	// int32 ViewportSizeX, ViewportSizeY;
	// GetViewportSize(ViewportSizeX, ViewportSizeY);
	// auto ScreenLocation = FVector2D(ViewportSizeX, ViewportSizeY);

	FVector2D MousePos = FVector2D(0, 0);
	FVector WorldLocation = FVector(MousePos.X, MousePos.Y, 0);
	FVector WorldDirection;
	GetMousePosition(MousePos.X, MousePos.Y);
	if(DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("WorldLocation: %s"), *WorldLocation.ToString());
	}
	
	FVector StartLocation = WorldLocation;
	FVector EndLocation = StartLocation +(WorldDirection* TraceDistance);

	FCollisionQueryParams TraceParms;
	FHitResult HitResult;

	GetWorld()->LineTraceSingleByObjectType(HitResult, WorldLocation, EndLocation, ObjectQueryParams);
	DrawDebugLine(GetWorld(), WorldLocation, EndLocation, FColor::Orange, false, 0.f,0,1);

	AActor* HitActor = HitResult.GetActor();
	if(HitActor)
	{
		DrawDebugLine(GetWorld(), WorldLocation, EndLocation, FColor::Blue, false, 2.f, 0, 1);
		APawn* TheActor = Cast<APawn>(HitActor);
		Possess(TheActor);

		ACameraActor* mainCamera = FindObject<ACameraActor>(GetWorld(), TEXT("CameraActor1"));
		SetViewTargetWithBlend(mainCamera);
		
		if(HitActor->Implements<USGamePlayInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);
			ISGamePlayInterface::Execute_Interact(HitActor, MyPawn);
		}
	}
	
}

void ASPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// EnableInput(this);
	InputComponent->BindAction("PrimaryInteract",IE_Pressed, this, &ASPlayerController::PrimaryInteract);
	InputComponent->BindAction("LeftMouseClick",IE_Pressed, this, &ASPlayerController::SelectionPressed);
	InputComponent->BindAction("LeftMouseClick",IE_Released, this, &ASPlayerController::SelectionReleased);
	InputComponent->BindAction("RightMouseClick", IE_Released, this, &ASPlayerController::MoveReleased);
	InputComponent->BindAxis("Forward", this, &ASPlayerController::MoveForward);
	// InputComponent->BindAction("PauseMenu", IE_Pressed, this, &ASPlayerController::TogglePauseMenu);
	
}

void ASPlayerController::SelectionPressed()
{
	if(HUDptr != nullptr)
	{
		HUDptr->InitialPoint = HUDptr->GetMousePos2D();
		HUDptr->bStartSelecting = true;
	}
	
}

void ASPlayerController::SelectionReleased()
{
	HUDptr->bStartSelecting = false;
	// SelectedActors = HUDptr->FoundActors;
}

void ASPlayerController::MoveReleased()
{
	if(SelectedActors.Num()>0)
	{
		for(int i = 0; i<SelectedActors.Num(); i++)
		{
			// FHitResult Hit;
			GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
			FVector MoveLocation = Hit.Location + FVector(i/2*100, i%2*100, 0);
			// UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActors[i]->GetInstigatorController(), MoveLocation);
		}
	}
}

void ASPlayerController::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	// Super::CalcCamera(DeltaTime, OutResult);
	OutResult.Location = FVector(-1696.168579, -595.024597,775.860718 );
	// GetPawn()->GetActorLocation() + FVector(0,100, 0);
	
	OutResult.Rotation = FRotator(-20,90,0);
}

