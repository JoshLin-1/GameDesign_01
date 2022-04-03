// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerController.h"

#include "DrawDebugHelpers.h"
#include "SGamePlayInterface.h"

ASPlayerController::ASPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	bEnableMouseOverEvents = false;
	TraceDistance = 10000.f; 
	
}

void ASPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PrimaryInteract();
}

void ASPlayerController::PrimaryInteract()
{

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner(); 
	
	FVector WorldLocation;
	FVector WorldDirection;
	
	if(DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("WorldLocation: %s"), *WorldLocation.ToString());
	}
	
	FVector StartLocation (WorldLocation.Z, WorldLocation.X, WorldLocation.Y);
	FVector EndLocation = WorldLocation +(WorldDirection* TraceDistance);

	FCollisionQueryParams TraceParms;
	FHitResult HitResult;

	GetWorld()->LineTraceSingleByObjectType(HitResult, WorldLocation, EndLocation, ObjectQueryParams);
	DrawDebugLine(GetWorld(), WorldLocation, EndLocation, FColor::Orange, false, 0.f,0,1);

	AActor* HitActor = HitResult.GetActor();
	if(HitActor)
	{
		DrawDebugLine(GetWorld(), WorldLocation, EndLocation, FColor::Blue, false, 2.f, 0, 1);
		
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
	InputComponent->BindAxis("PrimaryInteract");
	
}

