// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyPath : ModuleRules
{
	public MyPath(ReadOnlyTargetRules Target) : base(Target)
	{
		// PrivateDependencyModuleNames.AddRange(new string[] { "AITestSuite" });

		//PrivateDependencyModuleNames.AddRange(new string[] { "Crunch" });
		//PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Slate", "SlateCore" });
	}
}
