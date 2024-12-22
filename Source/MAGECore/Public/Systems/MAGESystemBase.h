// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "Interfaces/MAGESystemInterface.h"
#include "MAGESystemBase.generated.h"

UCLASS(Abstract)
class MAGECORE_API UMAGESystemBase : public UObject, public IMAGESystemInterface
{
	GENERATED_BODY()
    
public:
	// IMAGESystemInterface
	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update(float DeltaTime) override;
	virtual void OnComponentRegistered(class UMAGEComponent* Component) override;
	virtual void OnComponentUnregistered(class UMAGEComponent* Component) override;
	virtual int32 GetUpdatePriority() const override { return UpdatePriority; }
	virtual bool DependsOn(const UClass* SystemClass) const override;
    
protected:
	UPROPERTY(EditDefaultsOnly, Category="MAGE")
	FGameplayTagContainer RequiredComponentTags;
    
	UPROPERTY(EditDefaultsOnly, Category="MAGE")
	int32 UpdatePriority = 0;
    
	UPROPERTY(EditDefaultsOnly, Category="MAGE")
	TArray<TSubclassOf<UObject>> SystemDependencies;
    
	UPROPERTY(Transient)
	TArray<TWeakObjectPtr<UMAGEComponent>> RegisteredComponents;
    
	bool DoesComponentMatchRequirements(const UMAGEComponent* Component) const;
};