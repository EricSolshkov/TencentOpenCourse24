// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Test54 : ModuleRules
{
	public Test54(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
