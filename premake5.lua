workspace "Summit"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

startproject "Summit"

project "Summit"
	location "Summit"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")	
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Summit/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src"
	}

	defines
	{
		"SUMMIT_CORE"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SUMMMIT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines 
		{
			"SUMMMIT_DEBUG",
			"SUMMMIT_ENABLE_ASSERTS"
		}
		symbols "on"

	filter "configurations:Release"
		defines "SUMMIT_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "SUMMIT_DIST"
		optimize "on"


