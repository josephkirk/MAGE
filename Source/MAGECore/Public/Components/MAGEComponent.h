// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Interfaces/MAGEComponentInterface.h"
#include "ModularGameplay/Public/Components/GameFrameworkComponent.h"
#include "MAGEComponent.generated.h"

UCLASS(Abstract, ClassGroup=MAGE, meta=(BlueprintSpawnableComponent))
class MAGECORE_API UMAGEComponent : public UActorComponent, public IMAGEComponentInterface
{
	GENERATED_BODY()
    
public:
	UMAGEComponent();
    
	// IMAGEComponentInterface
	virtual FGameplayTagContainer GetMageComponentTags() const override;
	virtual void OnSystemRegistered(TScriptInterface<IMAGESystemInterface> System) override;
	virtual void OnSystemUnregistered(TScriptInterface<IMAGESystemInterface> System) override;
    
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    
	UPROPERTY(EditDefaultsOnly, Category="MAGE")
	FGameplayTagContainer MAGEComponentTags;
    
	UPROPERTY(Transient)
	TArray<TScriptInterface<IMAGESystemInterface>> RegisteredSystems;
    
private:
	void RegisterWithMAGE();
	void UnregisterFromMAGE();
};
