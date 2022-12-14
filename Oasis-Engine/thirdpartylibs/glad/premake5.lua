project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"
	cdialect "C17"

	targetdir ("../../../Build/%{prj.name}/" .. outputdir .. "/Binaries")
	objdir ("../../../Build/%{prj.name}/" .. outputdir .. "/CompilerData")

	files {
		"include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
	}

	includedirs {
		"include"
	}

	filter "system:windows"
		systemversion "latest"
        staticruntime "On"

	filter {"system:windows", "configurations:Debug"}
		runtime "Debug"
		symbols "on"

	filter {"system:windows", "configurations:Release"}
		runtime "Release"
		optimize "on"

	filter {"system:windows", "configurations:Distribution"}
		runtime "Release"
		optimize "on"
        symbols "off"   