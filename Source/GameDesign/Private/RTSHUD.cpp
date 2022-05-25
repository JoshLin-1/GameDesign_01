// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHUD.h"

#include "SMissleSample.h"
#include "SPlayerController.h"

void ARTSHUD::DrawHUD()
{
	// Super::DrawHUD();
	if(bStartSelecting == true)
	{
		if(FoundActors.Num() > 0)
		{
			for(int32 i = 0; i<FoundActors.Num(); i++)
			{
				FoundActors[i]->SetDeSelected();
			}
		}
		FoundActors.Empty();
		
		CurrentPoint = GetMousePos2D();
		DrawRect(FLinearColor(0,0,1,.15f),InitialPoint.X, InitialPoint.Y,CurrentPoint.X-InitialPoint.X,CurrentPoint.Y-InitialPoint.Y);
		GetActorsInSelectionRectangle<ASMissleSample>(InitialPoint, CurrentPoint, FoundActors, false, false);

		if(FoundActors.Num() > 0)
		{
			for (int32 i = 0; i<FoundActors.Num(); i++)
			{
				FoundActors[i]->SetSelected();
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Start make rectengle"))
	}
}

FVector2D ARTSHUD::GetMousePos2D()
{
	float PosX;
	float PosY;
	
	GetOwningPlayerController()->GetMousePosition(PosX, PosY);

	return FVector2D(PosX,PosY);
}
