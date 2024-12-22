#include "Systems/MAGESubsystem.h"
#include "Components/MAGEComponent.h"

DECLARE_STATS_GROUP(TEXT("MAGE"), STATGROUP_MAGE, STATCAT_Advanced);
DECLARE_CYCLE_STAT(TEXT("Tick Mage System"), STAT_MAGESubsystem_Tick, STATGROUP_MAGE);

void UMAGESubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
    
	if (UWorld* World = GetWorld())
	{
		TickDelegateHandle = World->OnTickDispatch().AddUObject(this, &UMAGESubsystem::Tick);
	}
}

void UMAGESubsystem::Deinitialize()
{
	if (UWorld* World = GetWorld())
	{
		World->OnTickDispatch().Remove(TickDelegateHandle);
	}
    
	for (auto& System : Systems)
	{
		if (System)
		{
			System->Shutdown();
		}
	}
    
	Systems.Empty();
	Components.Empty();
    
	Super::Deinitialize();
}

void UMAGESubsystem::RegisterSystem(TScriptInterface<IMAGESystemInterface> System)
{
	if (System)
	{
		Systems.Add(System);
		System->Initialize();
        
		// Register existing components with new system
		for (auto ComponentPtr : Components)
		{
			if (UMAGEComponent* Component = ComponentPtr.Get())
			{
				System->OnComponentRegistered(Component);
			}
		}
        
		SortSystems();
	}
}

void UMAGESubsystem::UnregisterSystem(TScriptInterface<IMAGESystemInterface> System)
{
	if (System)
	{
		// Unregister components from system
		for (auto ComponentPtr : Components)
		{
			if (UMAGEComponent* Component = ComponentPtr.Get())
			{
				System->OnComponentUnregistered(Component);
			}
		}
        
		System->Shutdown();
		Systems.Remove(System);
	}
}

void UMAGESubsystem::RegisterComponent(UMAGEComponent* Component)
{
	if (Component)
	{
		Components.Add(Component);
        
		// Register component with existing systems
		for (auto& System : Systems)
		{
			if (System)
			{
				System->OnComponentRegistered(Component);
			}
		}
	}
}

void UMAGESubsystem::UnregisterComponent(UMAGEComponent* Component)
{
	if (Component)
	{
		// Unregister component from systems
		for (auto& System : Systems)
		{
			if (System)
			{
				System->OnComponentUnregistered(Component);
			}
		}
        
		Components.Remove(Component);
	}
}

void UMAGESubsystem::Tick(float DeltaTime)
{
#if WITH_EDITOR || MAGE_DEBUG
	SCOPE_CYCLE_COUNTER(STAT_MAGESubsystem_Tick);
#endif

	// Update all systems in priority order
	for (auto& System : Systems)
	{
		if (System)
		{
			System->Update(DeltaTime);
		}
	}
}

void UMAGESubsystem::SortSystems()
{
	// Sort systems by priority and dependencies
	Systems.Sort([](const TScriptInterface<IMAGESystemInterface>& A, const TScriptInterface<IMAGESystemInterface>& B)
	{
		if (!A || !B) return false;
        
		// Check dependencies first
		if (A->DependsOn(B->GetClass())) return false;
		if (B->DependsOn(A->GetClass())) return true;
        
		// Then check priorities
		return A->GetUpdatePriority() > B->GetUpdatePriority();
	});
}