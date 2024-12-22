

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/MAGESystemInterface.h"
#include "MAGESubsystem.generated.h"



UCLASS()
class MAGECORE_API UMAGESubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
    
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
    
	void RegisterSystem(TScriptInterface<IMAGESystemInterface> System);
	void UnregisterSystem(TScriptInterface<IMAGESystemInterface> System);
	void RegisterComponent(class UMAGEComponent* Component);
	void UnregisterComponent(class UMAGEComponent* Component);
    
	void Tick(float DeltaTime);
    
protected:
	UPROPERTY()
	TArray<TScriptInterface<IMAGESystemInterface>> Systems;
    
	UPROPERTY()
	TArray<TWeakObjectPtr<UMAGEComponent>> Components;
    
private:
	void SortSystems();
	FDelegateHandle TickDelegateHandle;
};
