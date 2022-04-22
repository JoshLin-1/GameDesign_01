// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGamePlayInterface.h"
#include "GameFramework/Actor.h"
#include "SMissleProjectileBase.generated.h"



class UCameraShakeBase;
class USphereComponent;
class UAudioComponent;
class USoundBase;
class UParticleSystem;
class UParticleSystemComponent;
class UPointLightComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;
class UStaticMeshComponent;

UCLASS()
class GAMEDESIGN_API ASMissleProjectileBase : public AActor, public ISGamePlayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	TSubclassOf<UCameraShakeBase> ImpactShake;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundBase* ImpactSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	UParticleSystem* ImpactVFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* EffectComp;

  	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAudioComponent* AudioComp;
	
  	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMeshComp; 

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	float ImpactShakeInnerRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	float ImpactShakeOuterRadius;

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	
public:	
	// Sets default values for this actor's properties
	ASMissleProjectileBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
