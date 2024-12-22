// Copyright Studio Koorogi Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "MAGESystemInterface.h"
#include "MAGEComponentInterface.generated.h"

UINTERFACE()
class MAGECORE_API UMAGEComponentInterface : public UInterface
{
	GENERATED_BODY()
};

class MAGECORE_API IMAGEComponentInterface
{
	GENERATED_BODY()
    
public:
	virtual FGameplayTagContainer GetMageComponentTags() const = 0;
	virtual void OnSystemRegistered(TScriptInterface<IMAGESystemInterface> System) = 0;
	virtual void OnSystemUnregistered(TScriptInterface<IMAGESystemInterface> System) = 0;
};