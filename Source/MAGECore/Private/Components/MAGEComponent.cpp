// Copyright Studio Koorogi Games, Inc. All Rights Reserved.


#include "Components/MAGEComponent.h"
#include "Systems/MAGESubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(MAGEComponent)

UMAGEComponent::UMAGEComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMAGEComponent::BeginPlay()
{
	Super::BeginPlay();
	RegisterWithMAGE();
}

void UMAGEComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterFromMAGE();
	Super::EndPlay(EndPlayReason);
}

FGameplayTagContainer UMAGEComponent::GetMageComponentTags() const
{
	return MAGEComponentTags;
}

void UMAGEComponent::OnSystemRegistered(TScriptInterface<IMAGESystemInterface> System)
{
	RegisteredSystems.Add(System);
}

void UMAGEComponent::OnSystemUnregistered(TScriptInterface<IMAGESystemInterface> System)
{
	RegisteredSystems.Remove(System);
}

void UMAGEComponent::RegisterWithMAGE()
{
	if (UWorld* World = GetWorld())
	{
		if (UMAGESubsystem* MAGESubsystem = World->GetGameInstance()->GetSubsystem<UMAGESubsystem>())
		{
			MAGESubsystem->RegisterComponent(this);
		}
	}
}

void UMAGEComponent::UnregisterFromMAGE()
{
	if (UWorld* World = GetWorld())
	{
		if (UMAGESubsystem* MAGESubsystem = World->GetGameInstance()->GetSubsystem<UMAGESubsystem>())
		{
			MAGESubsystem->UnregisterComponent(this);
		}
	}
}