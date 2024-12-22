// Copyright Studio Koorogi Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MAGESystemInterface.generated.h"

UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class MAGECORE_API UMAGESystemInterface : public UInterface
{
	GENERATED_BODY()
};

class MAGECORE_API IMAGESystemInterface
{
	GENERATED_BODY()
    
public:
	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void OnComponentRegistered(class UMAGEComponent* Component) = 0;
	virtual void OnComponentUnregistered(class UMAGEComponent* Component) = 0;
	virtual int32 GetUpdatePriority() const = 0;
	virtual bool DependsOn(const UClass* SystemClass) const = 0;

	UClass* GetClass() { return Cast<UClass>(this); }
};