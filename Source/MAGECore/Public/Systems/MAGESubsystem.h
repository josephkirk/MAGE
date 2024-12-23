

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
    
	void RegisterSystem(TScriptInterface<IMAGESystemInterface> System);
	void UnregisterSystem(TScriptInterface<IMAGESystemInterface> System);
	void RegisterComponent(class UMAGEComponent* Component);
	void UnregisterComponent(class UMAGEComponent* Component);

 // Blueprint accessor
    UFUNCTION(BlueprintPure, Category = "MAGE|System", meta = (DisplayName = "Get MAGE Subsystem"))
    static UMAGESubsystem* Get(const UObject* WorldContextObject);
    
    // Registration functions exposed to blueprints
    UFUNCTION(BlueprintCallable, Category = "MAGE|System", meta = (DisplayName = "Register System"))
    bool RegisterSystemBP(UObject* System);
    
    UFUNCTION(BlueprintCallable, Category = "MAGE|System", meta = (DisplayName = "Unregister System"))
    bool UnregisterSystemBP(UObject* System);
    
    UFUNCTION(BlueprintCallable, Category = "MAGE|System", meta = (DisplayName = "Register Component"))
    bool RegisterComponentBP(UMAGEComponent* Component);
    
    UFUNCTION(BlueprintCallable, Category = "MAGE|System", meta = (DisplayName = "Unregister Component"))
    bool UnregisterComponentBP(UMAGEComponent* Component);
    
    // Query functions for blueprints
    UFUNCTION(BlueprintPure, Category = "MAGE|System")
    TArray<UObject*> GetRegisteredSystems() const;
    
    UFUNCTION(BlueprintPure, Category = "MAGE|System", meta=(DeterminesOutputType="SystemClass"))
    UObject* GetSystemByClass(TSubclassOf<UObject> SystemClass) const;
    
    UFUNCTION(BlueprintPure, Category = "MAGE|System")
    TArray<UMAGEComponent*> GetRegisteredComponents() const;

	// Debug helpers
	UFUNCTION(BlueprintCallable, Category = "MAGE|Debug")
	void DrawDebugInfo(bool bEnabled);
    
	UFUNCTION(BlueprintPure, Category = "MAGE|Debug")
	FString GetSystemDebugString() const;
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UPROPERTY()
	TArray<TScriptInterface<IMAGESystemInterface>> Systems;
    
	UPROPERTY()
	TArray<TWeakObjectPtr<UMAGEComponent>> Components;
    
private:
	bool bShowDebug=false;
	static bool ValidateSystem(const UObject* System);
	void Tick(float DeltaTime);
	void SortSystems();
	FDelegateHandle TickDelegateHandle;
};
