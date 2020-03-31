project "Test"
		
		location "../Test"
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
			"../../OpsCore/src",
			"../../%{IncludeDir.spdlog}",
			"../../%{IncludeDir.glm}", 
			"../../%{IncludeDir.imgui}",
			"../../%{IncludeDir.glfw}",
			"../../%{IncludeDir.glad}",
			"../../%{IncludeDir.catch2}"
		}

		links {
			"GLFW", 
			"Glad", 
			"ImGui",
			"OpsCore"
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
			defines "OC_DEBUG"
			buildoptions "/MDd"
			symbols "On"

			
		filter {"system:windows", "configurations:Release"}
			defines "OC_RELEASE"
			buildoptions "/MD"
			optimize "On"
	
		filter {"system:macosx", "configurations:Debug"}
			defines "OC_DEBUG"
			symbols "On"

		filter {"system:macosx", "configurations:Release"}
			defines "OC_RELEASE"
			optimize "On"
			
		filter {"system:linux", "configurations:Debug"}
			defines "OC_DEBUG"
			symbols "On"