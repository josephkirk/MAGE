#include "Systems/HealthSystem.h"
#include "Components/HealthComponent.h"

UHealthSystem::UHealthSystem()
{
    UpdatePriority = 100;
    RequiredComponentTags.AddTag(FGameplayTag::RequestGameplayTag("Component.Health"));
}

void UHealthSystem::Update(float DeltaTime)
{
    Super::Update(DeltaTime);
    
    ProcessHealthRegeneration(DeltaTime);
    CheckHealthStatus();
}

void UHealthSystem::ProcessHealthRegeneration(float DeltaTime)
{
    for (auto& ComponentPtr : RegisteredComponents)
    {
        if (UHealthComponent* HealthComp = Cast<UHealthComponent>(ComponentPtr.Get()))
        {
            if (HealthComp->bCanRegenerate && HealthComp->CurrentHealth < HealthComp->MaxHealth)
            {
                const float NewHealth = FMath::Min(
                    HealthComp->CurrentHealth + (HealthComp->RegenerationRate * DeltaTime),
                    HealthComp->MaxHealth
                );
                HealthComp->SetCurrentHealth(NewHealth);
            }
        }
    }
}