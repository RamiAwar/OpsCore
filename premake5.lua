workspace "OpsCore"
	
	architecture "x64"
	startproject "GridSearch"
	
	configurations 
	{ 
		"Debug", 
		"Release", 
		"Dist" 
	}


	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	-- Include directories relative to root folder
	IncludeDir = {}
	-- IncludeDir["GridSearch"] = "
	-- include "GridSearch/"
	IncludeDir["glm"] = "OpsCore/vendor/glm"
	IncludeDir["imgui"] = "OpsCore/vendor/imgui"
	IncludeDir["glfw"] = "OpsCore/vendor/GLFW/include"
	IncludeDir["glad"] = "OpsCore/vendor/Glad/include"
	IncludeDir["spdlog"] = "OpsCore/vendor/spdlog/include"


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
			"%{IncludeDir.glm}/glm/**.inl"
		}

		includedirs
		{
			"%{prj.name}/src",
			"%{IncludeDir.spdlog}",
			"%{IncludeDir.glfw}",
			"%{IncludeDir.glad}",
			"%{IncludeDir.imgui}",
			"%{IncludeDir.glm}"
		}

		links{
			"GLFW",
			"opengl32.lib",
			"Glad",
			"ImGui"
		}

		filter "system:macosx"
			systemversion "latest"
			defines
			{
				"GLFW_INCLUDE_NONE"
			}

		filter "system:windows"
			systemversion "latest"

			defines
			{
				"OC_BUILD_DLL",
				"GLFW_INCLUDE_NONE"
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
			

	project "Sandbox"
		
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h", 
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"OpsCore/src",
			"%{IncludeDir.spdlog}",
			"%{IncludeDir.glm}", 
			"%{IncludeDir.imgui}",
			"%{IncludeDir.glfw}",
			"%{IncludeDir.glad}",
		}

		filter "system:windows"
			links
			{
				"GLFW", 
				"Glad", 
				"ImGui", 
				"OpsCore"
			}
		
		filter "system:macosx"
			staticruntime "On"
			systemversion "latest"

			links
			{
				"Cocoa.framework",
				"IOKit.framework",
				"GLFW", "Glad", "ImGui", "OpsCore"
			}

			defines
			{
				"_GLFW_COCOA"
			}

		filter "system:windows"
			staticruntime "On"
			systemversion "latest"

			defines
			{

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

	project "Glad"
		kind "StaticLib"
		language "C"
		staticruntime "on"

		targetdir("bin/" .. outputdir .. "/%{prj.name}")
		objdir("bin-int/" .. outputdir .. "/%{prj.name}")

		glad_dir = "OpsCore/vendor/%{prj.name}/"

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
		

	project "GLFW"
		kind "StaticLib"
		language "C"
		staticruntime "on"

		targetdir("bin/" .. outputdir .. "/%{prj.name}")
		objdir("bin-int/" .. outputdir .. "/%{prj.name}")

		glfw_dir = "OpsCore/vendor/GLFW/"

		files{
			glfw_dir .. "include/GLFW/glfw3.h",
			glfw_dir .. "include/GLFW/glfw3native.h",
			glfw_dir .. "src/glfw_config.h",
			glfw_dir .. "src/context.c",
			glfw_dir .. "src/init.c",
			glfw_dir .. "src/input.c",
			glfw_dir .. "src/monitor.c",
			glfw_dir .. "src/vulkan.c",
			glfw_dir .. "src/window.c",
			glfw_dir .. "src/egl_context.c",
			glfw_dir .. "src/osmesa_context.c"
		}

		filter "system:windows"
			systemversion "latest"

			files
			{
				glfw_dir .. "src/win32_init.c",
				glfw_dir .. "src/win32_joystick.c",
				glfw_dir .. "src/win32_monitor.c",
				glfw_dir .. "src/win32_time.c",
				glfw_dir .. "src/win32_thread.c",
				glfw_dir .. "src/win32_window.c",
				glfw_dir .. "src/wgl_context.c"

			}

			defines 
			{ 
				"_GLFW_WIN32",
				"_CRT_SECURE_NO_WARNINGS"
			}

		filter "system:linux"

			pic "On"

			systemversion "latest"

			files
			{
				glfw_dir .. "src/x11_init.c",
				glfw_dir .. "src/x11_monitor.c",
				glfw_dir .. "src/x11_window.c",
				glfw_dir .. "src/xkb_unicode.c",
				glfw_dir .. "src/posix_time.c",
				glfw_dir .. "src/posix_thread.c",
				glfw_dir .. "src/glx_context.c",
				glfw_dir .. "src/egl_context.c",
				glfw_dir .. "src/osmesa_context.c",
				glfw_dir .. "src/linux_joystick.c"
			}

			defines
			{
				"_GLFW_X11"
			}

			links
			{
				"dl",
				"m",
				"GL",
				"GLU",
				"X11",
				"Xinerama",
				"Xi",
				"Xcursor",
				"Xxf86vm",
				"pthread"
			}

		filter "system:macosx"
			
			pic "On"
			systemversion "latest"
			staticruntime "On"

			files
			{
				glfw_dir .. "src/cocoa_init.m",
				glfw_dir .. "src/cocoa_joystick.h",
				glfw_dir .. "src/cocoa_joystick.m",
				glfw_dir .. "src/cocoa_monitor.m",
				glfw_dir .. "src/cocoa_platform.h",
				glfw_dir .. "src/cocoa_time.c",
				glfw_dir .. "src/cocoa_window.m",
				glfw_dir .. "src/nsgl_context.m",
				glfw_dir .. "src/posix_thread.c"

			}

			defines
			{
				"_GLFW_COCOA"
			}


			links
			{
				"CoreFoundation.framework",
				"Cocoa.framework",
				"IOKit.framework",
				"CoreVideo.framework"
			}

		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			runtime "Release"
			optimize "on"

	project "ImGui"
		kind "StaticLib"
		language "C++"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		imgui_dir = "OpsCore/vendor/imgui/"

		files{
			imgui_dir .. "imconfig.h",
			imgui_dir .. "imgui.h",
			imgui_dir .. "imgui.cpp",
			imgui_dir .. "imgui_draw.cpp",
			imgui_dir .. "imgui_internal.h",
			imgui_dir .. "imgui_widgets.cpp",
			imgui_dir .. "imstb_rectpack.h",
			imgui_dir .. "imstb_textedit.h",
			imgui_dir .. "imstb_truetype.h",
			imgui_dir .. "imgui_demo.cpp"
		}

		filter "system:windows"
			systemversion "latest"
			cppdialect "C++17"

		filter {"system:windows", "configurations:Release"}
			buildoptions "/MT"

		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			runtime "Release"
			optimize "on"
			