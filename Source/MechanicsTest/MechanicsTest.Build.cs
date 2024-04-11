// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MechanicsTest : ModuleRules
{
	public MechanicsTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"EnhancedInput",
			"CableComponent"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[] {
			"CableComponent"
		});
	}
}
