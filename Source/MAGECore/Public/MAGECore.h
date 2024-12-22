// Copyright Studio Koorogi Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

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
