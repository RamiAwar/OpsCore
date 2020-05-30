workspace "PumpkinBox"
	
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
	IncludeDir["glm"] = "PumpkinBox/vendor/glm"
	IncludeDir["imgui"] = "PumpkinBox/vendor/imgui"
	IncludeDir["glfw"] = "PumpkinBox/vendor/GLFW/include"
	IncludeDir["glad"] = "PumpkinBox/vendor/Glad/include"
	IncludeDir["spdlog"] = "PumpkinBox/vendor/spdlog/include"
	IncludeDir["catch2"] = "PumpkinBox/vendor/Catch2"



	-- EXAMPLE PROJECTS INCLUDES
	include "Examples/Pong/pong.premake5.lua"
	include "Examples/Sandbox/sandbox.premake5.lua"  
	include "Examples/EcsTest/ecstest.premake5.lua"  
	include "Examples/Platformer/platformer.premake5.lua"
	
	-- DEPENDENCIES INCLUDES
	include "PumpkinBox/vendor/glad.premake5.lua"
	include "PumpkinBox/vendor/glfw.premake5.lua"
	include "PumpkinBox/vendor/imgui.premake5.lua"


	-- OPSCORE PROJECT BUILD CONFIGURATION
	project "PumpkinBox"
		
		location "PumpkinBox"
		kind "StaticLib"
		language "C++"
		staticruntime "on"
		cppdialect "C++17"


		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		-- Precompiled headers
		pchheader "pbpch.h"
		pchsource "%{prj.name}/src/pbpch.cpp" -- only necessary for visual studio

		

		files
		{
			"%{prj.name}/src/**.h", 
			"%{prj.name}/src/**.cpp",
			"%{IncludeDir.glm}/glm/**.hpp",
			"%{IncludeDir.glm}/glm/**.inl",
			"%{IncludeDir.catch2}/catch2.hpp"		

		}

		includedirs
		{
			"%{prj.name}/src",
			"%{IncludeDir.spdlog}",
			"%{IncludeDir.glfw}",
			"%{IncludeDir.glad}",
			"%{IncludeDir.imgui}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.catch2}"		

		}

		links{
			"GLFW",
			"opengl32.lib",
			"Glad",
			"ImGui"		
		}

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
			defines "PB_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter {"system:windows", "configurations:Release"}
			defines "PB_RELEASE"
			buildoptions "/MD"
			optimize "On"
			
		filter {"system:windows", "configurations:Dist"}
			defines "PB_DIST"
			buildoptions "/MD"
			optimize "On"
			
		filter {"system:macosx", "configurations:Debug"}
			defines "PB_DEBUG"
			symbols "On"
			
		filter {"system:macosx", "configurations:Release"}
			defines "PB_RELEASE"
			optimize "On"
			
		filter {"system:macosx", "configurations:Dist"}
			defines "PB_RELEASE"
			optimize "On"

		filter {"system:linux", "configurations:Debug"}
			defines "PB_DEBUG"
			symbols "On"

	


