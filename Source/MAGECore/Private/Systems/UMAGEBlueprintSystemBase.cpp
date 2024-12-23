#include "Systems/MAGEBlueprintSystemBase.h"
#include "Components/MAGEComponent.h"
#include "MAGECore.h"
#include "DrawDebugHelpers.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(MAGEBlueprintSystemBase)
UMAGEBlueprintSystemBase::UMAGEBlueprintSystemBase()
{
    bAutoActivate = true;
    BlueprintUpdatePriority = 0;
}

void UMAGEBlueprintSystemBase::Initialize()
{
    Super::Initialize();
    
    // Update required tags from blueprint configuration
    RequiredComponentTags.AppendTags(RequiredComponentTagsForBlueprint);
    UpdatePriority = BlueprintUpdatePriority;
    
    // Call blueprint event
    ReceiveInitialize();
}

void UMAGEBlueprintSystemBase::Shutdown()
{
    // Call blueprint event
    ReceiveShutdown();
    
    Super::Shutdown();
}

void UMAGEBlueprintSystemBase::Update(float DeltaTime)
{
    Super::Update(DeltaTime);
    
    // Broadcast tick event
    OnSystemTick.Broadcast(DeltaTime);
    
    // Call blueprint event
    ReceiveUpdate(DeltaTime);
}

void UMAGEBlueprintSystemBase::OnComponentRegistered(UMAGEComponent* Component)
{
    Super::OnComponentRegistered(Component);
    
    if (Component)
    {
        // Broadcast component registered event
        OnComponentRegisteredEvent.Broadcast(Component);
        
        // Call blueprint event
        ReceiveComponentRegistered(Component);
    }
}

void UMAGEBlueprintSystemBase::OnComponentUnregistered(UMAGEComponent* Component)
{
    if (Component)
    {
        // Broadcast component unregistered event
        OnComponentUnregisteredEvent.Broadcast(Component);
        
        // Call blueprint event
        ReceiveComponentUnregistered(Component);
    }
    
    Super::OnComponentUnregistered(Component);
}

TArray<UMAGEComponent*> UMAGEBlueprintSystemBase::GetRegisteredComponents() const
{
    TArray<UMAGEComponent*> Result;
    for (const auto& WeakComponent : RegisteredComponents)
    {
        if (UMAGEComponent* Component = WeakComponent.Get())
        {
            Result.Add(Component);
        }
    }
    return Result;
}

TArray<UMAGEComponent*> UMAGEBlueprintSystemBase::GetRegisteredComponentsByClass(TSubclassOf<UMAGEComponent> ComponentClass) const
{
    TArray<UMAGEComponent*> Result;
    if (!ComponentClass) return Result;
    
    for (const auto& WeakComponent : RegisteredComponents)
    {
        if (UMAGEComponent* Component = WeakComponent.Get())
        {
            if (Component->IsA(ComponentClass))
            {
                Result.Add(Component);
            }
        }
    }
    return Result;
}

TArray<UMAGEComponent*> UMAGEBlueprintSystemBase::GetRegisteredComponentsByTags(const FGameplayTagContainer& Tags, bool bRequireAll) const
{
    TArray<UMAGEComponent*> Result;
    if (Tags.IsEmpty()) return Result;
    
    for (const auto& WeakComponent : RegisteredComponents)
    {
        if (UMAGEComponent* Component = WeakComponent.Get())
        {
            const FGameplayTagContainer& ComponentTags = Component->GetMageComponentTags();
            if (bRequireAll ? ComponentTags.HasAll(Tags) : ComponentTags.HasAny(Tags))
            {
                Result.Add(Component);
            }
        }
    }
    return Result;
}

void UMAGEBlueprintSystemBase::DrawDebugString(const FString& Text, const FColor& Color, float Duration)
{
    if (UWorld* World = GetWorld())
    {
        GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Text);
    }
}

void UMAGEBlueprintSystemBase::DrawDebugSphere(const FVector& Location, float Radius, const FColor& Color, float Duration)
{
    if (UWorld* World = GetWorld())
    {
        ::DrawDebugSphere(World, Location, Radius, 12, Color, false, Duration);
    }
}

// Default implementations for blueprint events
void UMAGEBlueprintSystemBase::ReceiveInitialize_Implementation() {}
void UMAGEBlueprintSystemBase::ReceiveShutdown_Implementation() {}
void UMAGEBlueprintSystemBase::ReceiveUpdate_Implementation(float DeltaTime) {}
void UMAGEBlueprintSystemBase::ReceiveComponentRegistered_Implementation(UMAGEComponent* Component) {}
void UMAGEBlueprintSystemBase::ReceiveComponentUnregistered_Implementation(UMAGEComponent* Component) {}

#if WITH_EDITOR
void UMAGEBlueprintSystemBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    
    // Update system configuration when properties change in editor
    if (PropertyChangedEvent.Property)
    {
        if (PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UMAGEBlueprintSystemBase, RequiredComponentTagsForBlueprint))
        {
            RequiredComponentTags.AppendTags(RequiredComponentTagsForBlueprint);
        }
        else if (PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UMAGEBlueprintSystemBase, BlueprintUpdatePriority))
        {
            UpdatePriority = BlueprintUpdatePriority;
        }
    }
}
#endif