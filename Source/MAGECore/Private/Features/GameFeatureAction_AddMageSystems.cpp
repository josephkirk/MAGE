#include "Features/GameFeatureAction_AddMageSystems.h"
#include "GameFeaturesSubsystem.h"
#include "Systems/MAGESubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GameFeatureAction_AddMageSystems)

#define LOCTEXT_NAMESPACE "GameFeatures"

struct FGameFeatureActivatingContext;

void UGameFeatureAction_AddMageSystems::OnGameFeatureActivating(FGameFeatureActivatingContext& Context)
{
	UMAGESubsystem* MAGESubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMAGESubsystem>();
	if (!MAGESubsystem) return;
    
	for (const TSubclassOf<UObject>& SystemClass : SystemClasses)
	{
		if (UObject* NewSystem = NewObject<UObject>(MAGESubsystem, SystemClass))
		{
			if (auto* System = Cast<IMAGESystemInterface>(NewSystem))
			{
				MAGESubsystem->RegisterSystem(NewSystem);
				SpawnedSystems.Add(NewSystem);
			}
		}
	}
}

void UGameFeatureAction_AddMageSystems::OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context)
{
	UMAGESubsystem* MAGESubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMAGESubsystem>();
	if (!MAGESubsystem) return;
    
	for (TWeakObjectPtr<UObject>& SystemPtr : SpawnedSystems)
	{
		if (UObject* System = SystemPtr.Get())
		{
			if (auto* MAGESystem = Cast<IMAGESystemInterface>(System))
			{
				MAGESubsystem->UnregisterSystem(System);
			}
		}
	}
    
	SpawnedSystems.Empty();
}
#undef LOCTEXT_NAMESPACE