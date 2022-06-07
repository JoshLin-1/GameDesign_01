// Fill out your copyright notice in the Description page of Project Settings.


#include "SMissleSample.h"

#include "RTSHUD.h"
#include "SWorldUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/DecalComponent.h"


// Sets default values
ASMissleSample::ASMissleSample()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	// static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("D:/My Project/Unreal Project/GitHub/GameDesign_01/Content/M_Mask_Inst.uasset"));
	// if(DecalMaterialAsset.Succeeded())
	// {
	// 	CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	// }

	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	CursorToWorld->SetVisibility(false);

}

// Called when the game starts or when spawned
void ASMissleSample::BeginPlay()
{
	Super::BeginPlay();
	
	
	if(ActiveRemainBullet == nullptr)
	{
		ActiveRemainBullet = CreateWidget<USWorldUserWidget>(GetWorld(), RemainBulletWidgetClass);
		if(ActiveRemainBullet)
		{
			ActiveRemainBullet->AttachedActor = this; 
			ActiveRemainBullet->AddToViewport();
		}
	}

	
}

void ASMissleSample::SetSelected()
{
	CursorToWorld->SetVisibility(true);
}

void ASMissleSample::SetDeSelected()
{
	CursorToWorld->SetVisibility(false);
}

// Called every frame
void ASMissleSample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASMissleSample::InteractToMousePosition_Implementation(FVector CursorPosition)
{
	ISGamePlayInterface::InteractToMousePosition_Implementation(CursorPosition);
}

void ASMissleSample::RightMouseInteract_Implementation()
{
	ISGamePlayInterface::RightMouseInteract_Implementation();
}

void ASMissleSample::MouseWhellInteract_Implementation(float Value)
{
	ISGamePlayInterface::MouseWhellInteract_Implementation(Value);
}


