// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WorldWidget : ModuleRules
{
	public WorldWidget (ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.Default;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { });

	}
}