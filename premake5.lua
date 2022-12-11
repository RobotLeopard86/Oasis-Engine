workspace "Oasis-Engine"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Distribution"
	}

	startproject "Oasis-Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Oasis-Engine/thirdpartylibs/glfw/include"
IncludeDir["GLAD"] = "Oasis-Engine/thirdpartylibs/glad/include"
IncludeDir["IMGUI"] = "Oasis-Engine/thirdpartylibs/imgui"
include "Oasis-Engine/thirdpartylibs/glfw"
include "Oasis-Engine/thirdpartylibs/glad"
include "Oasis-Engine/thirdpartylibs/imgui"

project "Oasis-Engine"
	location "Oasis-Engine"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

	targetdir ("Build/%{prj.name}/" .. outputdir .. "/Binaries")
	objdir ("Build/%{prj.name}/" .. outputdir .. "/CompilerData")

	pchheader "OasisPCH.h"
	pchsource "Oasis-Engine/src/OasisPCH.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.hpp"
	}

	includedirs {
		"%{prj.name}/thirdpartylibs/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.IMGUI}"
	}

	links {
		"GLFW",
		"GLAD",
		"IMGUI",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		cdialect "C17"
		systemversion "10.0.22621.0"

		defines {
			"OE_PLATFORM_WIN",
			"OE_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../Build/Oasis-Sandbox/" .. outputdir .. "/Binaries")
		}

	filter "configurations:Debug"
		defines {
			"OE_DEBUG",
			"OE_ALLOWASSERTS"
		}
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "OE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Distribution"
		defines "OE_DIST"
		runtime "Release"
		optimize "On"

project "Oasis-Sandbox"
	location "Oasis-Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

	targetdir ("Build/%{prj.name}/" .. outputdir .. "/Binaries")
	objdir ("Build/%{prj.name}/" .. outputdir .. "/CompilerData")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.hpp"
	}

	includedirs {
		"Oasis-Engine/thirdpartylibs/glfw/include",
		"Oasis-Engine/thirdpartylibs/spdlog/include",
		"Oasis-Engine/src",
	}

	links {
		"Oasis-Engine"
	}

	filter "system:windows"
		cppdialect "C++20"
		cdialect "C17"
		systemversion "10.0.22621.0"

		defines {
			"OE_PLATFORM_WIN",
		}

	filter "configurations:Debug"
		defines "OE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "OE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Distribution"
		defines "OE_DIST"
		runtime "Release"
		optimize "On"