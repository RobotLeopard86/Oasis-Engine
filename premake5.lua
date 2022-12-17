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
IncludeDir["SPDLOG"] = "Oasis-Engine/thirdpartylibs/spdlog/include"
IncludeDir["GLAD"] = "Oasis-Engine/thirdpartylibs/glad/include"
IncludeDir["IMGUI"] = "Oasis-Engine/thirdpartylibs/imgui"
IncludeDir["GLM"] = "Oasis-Engine/thirdpartylibs/glm/"
include "Oasis-Engine/thirdpartylibs/glfw"
include "Oasis-Engine/thirdpartylibs/glad"
include "Oasis-Engine/thirdpartylibs/imgui"

project "Oasis-Engine"
	location "Oasis-Engine"
	kind "StaticLib"
	language "C++"
	staticruntime "On"
	cppdialect "C++20"
	cdialect "C17"

	targetdir ("Build/%{prj.name}/" .. outputdir .. "/Binaries")
	objdir ("Build/%{prj.name}/" .. outputdir .. "/CompilerData")

	pchheader "OasisPCH.h"
	pchsource "Oasis-Engine/src/OasisPCH.cpp"

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/thirdpartylibs/glm/glm/**.hpp",
		"%{prj.name}/thirdpartylibs/glfw/include/**.h",
		"%{prj.name}/thirdpartylibs/glm/glm/**.inl"
	}

	includedirs {
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.IMGUI}",
		"%{IncludeDir.SPDLOG}",
		"%{IncludeDir.GLM}"
	}

	links {
		"GLFW",
		"GLAD",
		"IMGUI",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"OE_PLATFORM_WIN",
			"OE_DLL",
			"GLFW_INCLUDE_NONE",
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
	staticruntime "On"
	cppdialect "C++20"
	cdialect "C17"

	targetdir ("Build/%{prj.name}/" .. outputdir .. "/Binaries")
	objdir ("Build/%{prj.name}/" .. outputdir .. "/CompilerData")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.hpp"
	}

	includedirs {
		"%{IncludeDir.SPDLOG}",
		"%{IncludeDir.GLM}",
		"Oasis-Engine/src",
		"Oasis-Engine/thirdpartylibs"
	}

	links {
		"Oasis-Engine"
	}

	filter "system:windows"
		systemversion "latest"

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