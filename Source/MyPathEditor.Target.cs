// Copyright Patrick Carvalho All Rights Reserved.
// sysware@sysware.com.br
// 

using UnrealBuildTool;
using System.Collections.Generic;

public class MyPathEditorTarget : TargetRules
{
    public MyPathEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("MyPath");
	}
}
