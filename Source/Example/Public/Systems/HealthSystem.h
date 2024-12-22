#pragma once

#include "CoreMinimal.h"
#include "Systems/MAGESystemBase.h"
#include "HealthSystem.generated.h"

UCLASS()
class MAGEEXAMPLE_API UHealthSystem : public UMAGESystemBase
{
    GENERATED_BODY()
    
public:
    UHealthSystem();
    
    virtual void Initialize() override;
    virtual void Update(float DeltaTime) override;
    
protected:
    virtual void OnComponentRegistered(UMAGEComponent* Component) override;
    virtual void OnComponentUnregistered(UMAGEComponent* Component) override;
    
private:
    void ProcessHealthRegeneration(float DeltaTime);
    void CheckHealthStatus();
};