

#pragma once

#include "CoreMinimal.h"
#include "GameFeatureAction.h"
#include "GameFeatureAction_AddMageSystems.generated.h"

UCLASS()
class MAGECORE_API UGameFeatureAction_AddMageSystems : public UGameFeatureAction
{
	GENERATED_BODY()
    
public:
	virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context) override;
	virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;
    
	UPROPERTY(EditDefaultsOnly, Category="MAGE")
	TArray<TSubclassOf<UObject>> SystemClasses;
    
private:
	TArray<TWeakObjectPtr<UObject>> SpawnedSystems;
};