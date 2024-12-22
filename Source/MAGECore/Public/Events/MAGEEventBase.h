

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MAGEEventBase.generated.h"

UCLASS(Abstract, Blueprintable)
class MAGECORE_API UMAGEEventBase : public UObject
{
	GENERATED_BODY()
    
public:
	UPROPERTY()
	class UObject* Instigator;
    
	UPROPERTY()
	class UObject* Target;
    
	//virtual FString GetDebugString() const;
};