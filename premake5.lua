workspace "summit"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

startproject "summit"

include "summit/vendor/zlib"
include "summit/vendor/mbedtls"
include "summit/vendor/curl"
include "summit/vendor/curlpp"

project "summit"
	location "summit"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")	
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "summit/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/zlib",
		"%{prj.name}/vendor/mbedtls/include",
		"%{prj.name}/vendor/curl/include",
		"%{prj.name}/vendor/curl/lib",
		"%{prj.name}/vendor/curlpp/include"
	}

	links
	{
		"curlpp"
	}

	defines
	{
		"SUMMIT_CORE",
		"CURL_STATICLIB"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SUMMIT_PLATFORM_WINDOWS"
		}
		links { "ws2_32.lib" }

	filter "configurations:Debug"
		defines 
		{
			"SUMMIT_DEBUG",
			"SUMMIT_ENABLE_ASSERTS",
			"DEBUGBUILD"
		}
		symbols "on"

	filter "configurations:Release"
		defines "SUMMIT_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "SUMMIT_DIST"
		optimize "on"


