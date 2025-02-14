// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PlatformerPRACTICE : ModuleRules
{
	public PlatformerPRACTICE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] { "PlatformerPRACTICE" });

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "Niagara" });
	}
}