#pragma once
#include "CoreMinimal.h"
#include "Engine.h"
#include "Modules/ModuleInterface.h"

class FWorldWidgetModule : public IModuleInterface
{
public:
	virtual void StartupModule();
	virtual void ShutdownModule();
};

IMPLEMENT_GAME_MODULE(FWorldWidgetModule, WorldWidget);

void FWorldWidgetModule::StartupModule()
{
	
}

void FWorldWidgetModule::ShutdownModule()
{
	
}
