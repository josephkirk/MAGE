// Copyright Studio Koorogi Games, Inc. All Rights Reserved.


#include "Systems/MAGESystemBase.h"
#include "Components/MAGEComponent.h"

void UMAGESystemBase::Initialize()
{
	// Base initialization
}

void UMAGESystemBase::Shutdown()
{
	RegisteredComponents.Empty();
}

void UMAGESystemBase::Update(float DeltaTime)
{
	// Base update
}

void UMAGESystemBase::OnComponentRegistered(UMAGEComponent* Component)
{
	if (Component && DoesComponentMatchRequirements(Component))
	{
		RegisteredComponents.Add(Component);
		Component->OnSystemRegistered(this);
	}
}

void UMAGESystemBase::OnComponentUnregistered(UMAGEComponent* Component)
{
	if (Component)
	{
		RegisteredComponents.Remove(Component);
		Component->OnSystemUnregistered(this);
	}
}

bool UMAGESystemBase::DependsOn(const UClass* SystemClass) const
{
	return SystemDependencies.Contains(SystemClass);
}

bool UMAGESystemBase::DoesComponentMatchRequirements(const UMAGEComponent* Component) const
{
	if (!Component) return false;
    
	const FGameplayTagContainer& ComponentTags = Component->GetMageComponentTags();
	return RequiredComponentTags.IsEmpty() || ComponentTags.HasAll(RequiredComponentTags);
}