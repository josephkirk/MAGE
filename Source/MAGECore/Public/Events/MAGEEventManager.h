

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MAGEEventManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMAGEEvent, class UMAGEEventBase*, Event);

UCLASS()
class MAGECORE_API UMAGEEventManager : public UObject
{
	GENERATED_BODY()
    
public:
	template<typename T>
	void RegisterEventHandler(const UObject* Listener, TFunction<void(T*)> Handler);
    
	template<typename T>
	void UnregisterEventHandler(const UObject* Listener);
    
	void BroadcastEvent(UMAGEEventBase* Event);
    
private:
	TMap<UClass*, TArray<TPair<TWeakObjectPtr<const UObject>, TFunction<void(UMAGEEventBase*)>>>> EventHandlers;
};

// Implementation of templates
template<typename T>
void UMAGEEventManager::RegisterEventHandler(const UObject* Listener, TFunction<void(T*)> Handler)
{
	static_assert(TIsDerivedFrom<T, UMAGEEventBase>::Value, "T must derive from UMAGEEventBase");
    
	if (!Listener) return;
    
	auto& Handlers = EventHandlers.FindOrAdd(T::StaticClass());
	Handlers.Add(TPair<TWeakObjectPtr<const UObject>, TFunction<void(UMAGEEventBase*)>>(
		Listener,
		[Handler](UMAGEEventBase* Event) { Handler(Cast<T>(Event)); }
	));
}

template<typename T>
void UMAGEEventManager::UnregisterEventHandler(const UObject* Listener)
{
	if (!Listener) return;
    
	if (auto* Handlers = EventHandlers.Find(T::StaticClass()))
	{
		Handlers->RemoveAll([Listener](const auto& HandlerPair)
		{
			return !HandlerPair.Key.IsValid() || HandlerPair.Key.Get() == Listener;
		});
	}
}