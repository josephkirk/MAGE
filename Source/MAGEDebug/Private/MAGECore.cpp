// Copyright Studio Koorogi Games, Inc. All Rights Reserved.

#include "MAGEDebug.h"

#define LOCTEXT_NAMESPACE "FMAGEModule"

void FMAGEDebugModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FMAGEDebugModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMAGEDebugModule, MAGEDebug)