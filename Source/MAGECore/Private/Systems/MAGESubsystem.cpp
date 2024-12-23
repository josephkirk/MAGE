#include "Systems/MAGESubsystem.h"
#include "Components/MAGEComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MAGECore.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(MAGESubsystem)
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


UMAGESubsystem* UMAGESubsystem::Get(const UObject* WorldContextObject)
{
    if (!WorldContextObject) return nullptr;
    
    if (UWorld* World = WorldContextObject->GetWorld())
    {
        if (UGameInstance* GameInstance = World->GetGameInstance())
        {
            return GameInstance->GetSubsystem<UMAGESubsystem>();
        }
    }
    return nullptr;
}

bool UMAGESubsystem::RegisterSystemBP(UObject* System)
{
    if (!ValidateSystem(System))
    {
        UE_LOG(LogMAGE, Warning, TEXT("Failed to register system: Invalid system object"));
        return false;
    }
    
    IMAGESystemInterface* MAGESystem = Cast<IMAGESystemInterface>(System);
    if (!MAGESystem)
    {
        UE_LOG(LogMAGE, Warning, TEXT("Failed to register system: Object does not implement IMAGESystemInterface"));
        return false;
    }
    
    RegisterSystem(System);
    return true;
}

bool UMAGESubsystem::UnregisterSystemBP(UObject* System)
{
    if (!ValidateSystem(System))
    {
        UE_LOG(LogMAGE, Warning, TEXT("Failed to unregister system: Invalid system object"));
        return false;
    }
    
    if (!System->GetClass()->ImplementsInterface(UMAGESystemInterface::StaticClass()))
    {
        UE_LOG(LogMAGE, Warning, TEXT("Failed to unregister system: Object does not implement IMAGESystemInterface"));
        return false;
    }
    
    UnregisterSystem(System);
    return true;
}

bool UMAGESubsystem::RegisterComponentBP(UMAGEComponent* Component)
{
    if (!Component)
    {
        UE_LOG(LogMAGE, Warning, TEXT("Failed to register component: Invalid component"));
        return false;
    }
    
    if (!Component->IsValidLowLevel())
    {
        UE_LOG(LogMAGE, Warning, TEXT("Failed to register component: Component is pending kill"));
        return false;
    }
    
    RegisterComponent(Component);
    return true;
}

bool UMAGESubsystem::UnregisterComponentBP(UMAGEComponent* Component)
{
    if (!Component)
    {
        UE_LOG(LogMAGE, Warning, TEXT("Failed to unregister component: Invalid component"));
        return false;
    }
    
    UnregisterComponent(Component);
    return true;
}

TArray<UObject*> UMAGESubsystem::GetRegisteredSystems() const
{
    TArray<UObject*> Result;
    for (const auto& System : Systems)
    {
        if (UObject* SystemObj = System.GetObject())
        {
            Result.Add(SystemObj);
        }
    }
    return Result;
}

UObject* UMAGESubsystem::GetSystemByClass(TSubclassOf<UObject> SystemClass) const
{
    if (!SystemClass) return nullptr;
    
    for (const auto& System : Systems)
    {
        if (UObject* SystemObj = System.GetObject())
        {
            if (SystemObj->IsA(SystemClass))
            {
                return SystemObj;
            }
        }
    }
    return nullptr;
}

TArray<UMAGEComponent*> UMAGESubsystem::GetRegisteredComponents() const
{
    TArray<UMAGEComponent*> Result;
    for (const auto& WeakComponent : Components)
    {
        if (UMAGEComponent* Component = WeakComponent.Get())
        {
            Result.Add(Component);
        }
    }
    return Result;
}

void UMAGESubsystem::DrawDebugInfo(bool bEnabled)
{
    bShowDebug = bEnabled;
}

FString UMAGESubsystem::GetSystemDebugString() const
{
    FString Result = TEXT("MAGE Systems:\n");
    
    for (const auto& System : Systems)
    {
        if (UObject* SystemObj = System.GetObject())
        {
            Result += FString::Printf(TEXT("- %s (Priority: %d)\n"), 
                *SystemObj->GetClass()->GetName(),
                System->GetUpdatePriority());
        }
    }
    
    Result += FString::Printf(TEXT("\nRegistered Components: %d"), Components.Num());
    return Result;
}

bool UMAGESubsystem::ValidateSystem(const UObject* System)
{
    return System && System->IsValidLowLevel();
}