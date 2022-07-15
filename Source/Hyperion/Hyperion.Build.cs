// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Hyperion : ModuleRules
{
	public Hyperion(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
