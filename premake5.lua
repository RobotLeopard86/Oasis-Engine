workspace "Oasis-Engine"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Oasis-Engine/thirdpartylibs/glfw/include"
IncludeDir["GLAD"] = "Oasis-Engine/thirdpartylibs/glad/include"
include "Oasis-Engine/thirdpartylibs/glfw"
include "Oasis-Engine/thirdpartylibs/glad"

project "Oasis-Engine"
	location "Oasis-Engine"
	kind "SharedLib"
	language "C++"

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
		"%{IncludeDir.GLAD}"
	}

	links {
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		cdialect "C17"
		staticruntime "On"
		systemversion "10.0.22621.0"

		defines {
			"OASIS_WIN",
			"OASISDLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../Build/Oasis-Sandbox/" .. outputdir .. "/Binaries")
		}

	filter "configurations:Debug"
		defines {
			"OASISDEBUG",
			"OASIS_ALLOWASSERTS"
		}
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "OASISRELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Distribution"
		defines "OASISDIST"
		buildoptions "/MD"
		optimize "On"

project "Oasis-Sandbox"
	location "Oasis-Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "10.0.22621.0"

		defines {
			"OASIS_WIN",
		}

	filter "configurations:Debug"
		defines "OASISDEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "OASISRELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Distribution"
		defines "OASISDIST"
		buildoptions "/MD"
		optimize "On"