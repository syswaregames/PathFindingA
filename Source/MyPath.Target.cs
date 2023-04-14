// Copyright Patrick Carvalho All Rights Reserved.
// sysware@sysware.com.br
// 

using UnrealBuildTool;
using System.Collections.Generic;

public class MyPathTarget : TargetRules
{
    public MyPathTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("MyPath");
	}
}
