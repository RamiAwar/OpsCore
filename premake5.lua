workspace "OpsCore"
	
	architecture "x64"
	startproject "SandboxApp"
	
	configurations 
	{ 
		"Debug", 
		"Release", 
		"Dist" 
	}


	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	

	IncludeDir = {}

	-- INCLUDE DIRECTORIES
	IncludeDir["glm"] = "OpsCore/vendor/glm"
	IncludeDir["imgui"] = "OpsCore/vendor/imgui"
	IncludeDir["glfw"] = "OpsCore/vendor/GLFW/include"
	IncludeDir["glad"] = "OpsCore/vendor/Glad/include"
	IncludeDir["spdlog"] = "OpsCore/vendor/spdlog/include"



	-- EXAMPLE PROJECTS INCLUDES
	include "Examples/Pong/pong.premake5.lua"
	include "Examples/Sandbox/sandbox.premake5.lua"  
	include "Examples/Platformer/platformer.premake5.lua"
	
	-- DEPENDENCIES INCLUDES
	include "OpsCore/vendor/glad.premake5.lua"
	include "OpsCore/vendor/glfw.premake5.lua"
	include "OpsCore/vendor/imgui.premake5.lua"


	-- OPSCORE PROJECT BUILD CONFIGURATION
	project "OpsCore"
		
		location "OpsCore"
		kind "StaticLib"
		language "C++"
		staticruntime "on"
		cppdialect "C++17"


		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		-- Precompiled headers
		pchheader "ocpch.h"
		pchsource "%{prj.name}/src/ocpch.cpp" -- only necessary for visual studio

		

		files
		{
			"%{prj.name}/src/**.h", 
			"%{prj.name}/src/**.cpp",
			"%{IncludeDir.glm}/glm/**.hpp",
			"%{IncludeDir.glm}/glm/**.inl",
		}

		includedirs
		{
			"%{prj.name}/src",
			"%{IncludeDir.spdlog}",
			"%{IncludeDir.glfw}",
			"%{IncludeDir.glad}",
			"%{IncludeDir.imgui}",
			"%{IncludeDir.glm}"		}

		links{
			"GLFW",
			"opengl32.lib",
			"Glad",
			"ImGui"		}

		defines
		{
			"GLFW_INCLUDE_NONE"
		}

		filter "system:linux"

			links
			{ 
				"Xrandr",
				"Xi",
				"GLEW",
				"GLU",
				"GL",
				"X11"
			}

		filter {"system:windows","configurations:Debug"}
			defines "OC_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter {"system:windows", "configurations:Release"}
			defines "OC_RELEASE"
			buildoptions "/MD"
			optimize "On"
			
		filter {"system:windows", "configurations:Dist"}
			defines "OC_DIST"
			buildoptions "/MD"
			optimize "On"
			
		filter {"system:macosx", "configurations:Debug"}
			defines "OC_DEBUG"
			symbols "On"
			
		filter {"system:macosx", "configurations:Release"}
			defines "OC_RELEASE"
			optimize "On"
			
		filter {"system:macosx", "configurations:Dist"}
			defines "OC_RELEASE"
			optimize "On"

		filter {"system:linux", "configurations:Debug"}
			defines "OC_DEBUG"
			symbols "On"

	


