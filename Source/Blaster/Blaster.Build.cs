// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Blaster : ModuleRules
{
	public Blaster(ReadOnlyTargetRules Target) : base(Target)
	{

		PublicDependencyModuleNames.AddRange(new string[] {  "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput",
																	"UMG", "AIModule", "GeometryCollectionEngine" , "Niagara" ,"NavigationSystem","MultiplayerSessions", "OnlineSubsystem"
																	,"OnlineSubsystemSteam"
		});

        PrivateIncludePaths.Add("Blaster");
    }
}
