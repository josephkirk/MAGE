// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/MAGESystemBase.h"
#include "MAGEBlueprintSystemBase.generated.h"

// Delegate for blueprint binding
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMAGEComponentRegisteredDelegate, UMAGEComponent*, Component);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMAGEComponentUnregisteredDelegate, UMAGEComponent*, Component);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMAGESystemTickDelegate, float, DeltaTime);

UCLASS(Blueprintable, Abstract)
class MAGECORE_API UMAGEBlueprintSystemBase : public UMAGESystemBase
{
    GENERATED_BODY()

public:
    UMAGEBlueprintSystemBase();

    // Core system overrides with blueprint exposure
    virtual void Initialize() override;
    virtual void Shutdown() override;
    virtual void Update(float DeltaTime) override;
    
    // Blueprint event delegates
    UPROPERTY(BlueprintAssignable, Category = "MAGE|Events")
    FMAGEComponentRegisteredDelegate OnComponentRegisteredEvent;
    
    UPROPERTY(BlueprintAssignable, Category = "MAGE|Events")
    FMAGEComponentUnregisteredDelegate OnComponentUnregisteredEvent;
    
    UPROPERTY(BlueprintAssignable, Category = "MAGE|Events")
    FMAGESystemTickDelegate OnSystemTick;

protected:
    // Blueprint overridable functions
    UFUNCTION(BlueprintNativeEvent, Category = "MAGE|System")
    void ReceiveInitialize();
    
    UFUNCTION(BlueprintNativeEvent, Category = "MAGE|System")
    void ReceiveShutdown();
    
    UFUNCTION(BlueprintNativeEvent, Category = "MAGE|System")
    void ReceiveUpdate(float DeltaTime);
    
    UFUNCTION(BlueprintNativeEvent, Category = "MAGE|System")
    void ReceiveComponentRegistered(UMAGEComponent* Component);
    
    UFUNCTION(BlueprintNativeEvent, Category = "MAGE|System")
    void ReceiveComponentUnregistered(UMAGEComponent* Component);

    // Blueprint helper functions
    UFUNCTION(BlueprintCallable, Category = "MAGE|Components")
    TArray<UMAGEComponent*> GetRegisteredComponents() const;
    
    UFUNCTION(BlueprintCallable, Category = "MAGE|Components", meta=(DeterminesOutputType="ComponentClass"))
    TArray<UMAGEComponent*> GetRegisteredComponentsByClass(TSubclassOf<UMAGEComponent> ComponentClass) const;
    
    UFUNCTION(BlueprintCallable, Category = "MAGE|Components")
    TArray<UMAGEComponent*> GetRegisteredComponentsByTags(const FGameplayTagContainer& Tags, bool bRequireAll = true) const;
    
    // Configuration properties exposed to blueprints
    UPROPERTY(EditDefaultsOnly, Category = "MAGE|Configuration")
    bool bAutoActivate;
    
    UPROPERTY(EditDefaultsOnly, Category = "MAGE|Configuration")
    FGameplayTagContainer RequiredComponentTagsForBlueprint;
    
    UPROPERTY(EditDefaultsOnly, Category = "MAGE|Configuration")
    int32 BlueprintUpdatePriority;

    // Debug helpers
    UFUNCTION(BlueprintCallable, Category = "MAGE|Debug")
    void DrawDebugString(const FString& Text, const FColor& Color = FColor::White, float Duration = 0.0f);
    
    UFUNCTION(BlueprintCallable, Category = "MAGE|Debug")
    void DrawDebugSphere(const FVector& Location, float Radius = 100.0f, const FColor& Color = FColor::Red, float Duration = 0.0f);

#if WITH_EDITOR
    // Editor-only functionality
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
    // Internal overrides from base system
    virtual void OnComponentRegistered(UMAGEComponent* Component) override;
    virtual void OnComponentUnregistered(UMAGEComponent* Component) override;
};
