project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir("../../bin/" .. outputdir .. "/%{prj.name}")
	objdir("../../bin-int/" .. outputdir .. "/%{prj.name}")

	glad_dir = "glad/"

	files{
		glad_dir .. "include/glad/glad.h",
		glad_dir .. "include/KHR/khrplatform.h",
		glad_dir .. "src/glad.c"
	}

	includedirs{
		glad_dir .. "include"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		pic "on"
		systemversion "latest"
		
	filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
	
