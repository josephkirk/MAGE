// Copyright Studio Koorogi Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

MAGECORE_API DECLARE_LOG_CATEGORY_EXTERN(LogMAGE, Log, All);

class FMAGECoreModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static FMAGECoreModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FMAGECoreModule>("MAGECore");
	}
};
