project "Pong"
		
	location "../Pong"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h", 
		"src/**.cpp"
	}

	includedirs
	{
		"../../PumpkinBox/src",
		"../../%{IncludeDir.spdlog}",
		"../../%{IncludeDir.glm}", 
		"../../%{IncludeDir.imgui}",
		"../../%{IncludeDir.glfw}",
		"../../%{IncludeDir.glad}",
	}

	links {
		"GLFW", 
		"Glad", 
		"ImGui",
		"PumpkinBox"
	}

	filter "system:linux"

	links
	{
		"Xrandr",
		"Xi",
		"GLEW",
		"GLU",
		"GL",
		"X11",
		"dl",
		"pthread"
	}
	
	filter "system:macosx"
		staticruntime "On"
		systemversion "latest"

		links
		{
			"Cocoa.framework",
			"IOKit.framework"
		}

		defines
		{
			"_GLFW_COCOA"
		}


	filter {"system:windows","configurations:Debug"}
		defines "PB_DEBUG"
		buildoptions "/MDd"
		symbols "On"

		
	filter {"system:windows", "configurations:Release"}
		defines "PB_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter {"system:macosx", "configurations:Debug"}
		defines "PB_DEBUG"
		symbols "On"

	filter {"system:macosx", "configurations:Release"}
		defines "PB_RELEASE"
		optimize "On"
		
	filter {"system:linux", "configurations:Debug"}
		defines "PB_DEBUG"
		symbols "On"
