#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MAGEDebugSubsystem.generated.h"

UCLASS()
class MAGEDEBUG_API UMAGEDebugSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
    
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    
    void ToggleSystemVisualization(bool bEnable);
    void ToggleComponentVisualization(bool bEnable);
    void TogglePerformanceOverlay(bool bEnable);
    
    void DrawDebugInfo();
    
private:
    bool bShowSystemVisualization;
    bool bShowComponentVisualization;
    bool bShowPerformanceOverlay;
    
    FDelegateHandle OnDrawDebugDelegateHandle;
};