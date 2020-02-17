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



	project "OpsCore"
		
		location "OpsCore"
		kind "StaticLib"
		language "C++"
		staticruntime "on"

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
			"%{prj.name}/vendor/spdlog/include",
			"%{prj.name}/vendor/GLFW/include",
			"%{prj.name}/vendor/Glad/include",
			"%{IncludeDir.imgui}",
			"%{IncludeDir.glm}"
		}

		links{
			"GLFW",
			"opengl32.lib",
			"Glad",
			"ImGui"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines
			{
				"OC_PLATFORM_WINDOWS",
				"OC_BUILD_DLL",
				"GLFW_INCLUDE_NONE"
			}

			--postbuildcommands
			--{
			--	("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
			--}

		filter "configurations:Debug"
			defines "OC_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "OC_RELEASE"
			buildoptions "/MD"
			optimize "On"
		
		filter "configurations:Dist"
			defines "OC_DIST"
			buildoptions "/MD"
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
			"OpsCore/vendor/spdlog/include",
			"OpsCore/src",
			"%{IncludeDir.glm}", 
			"%{IncludeDir.imgui}"
		}

		links
		{
			"OpsCore" 
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines
			{
				"OC_PLATFORM_WINDOWS"
			}

		filter "configurations:Debug"
			defines "OC_DEBUG"
			buildoptions "/MDd"
			symbols "on"

		filter "configurations:Release"
			defines "OC_RELEASE"
			buildoptions "/MD"
			optimize "on"
		
		filter "configurations:Dist"
			defines "OC_DIST"
			buildoptions "/MD"
			optimize "on"

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

		glfw_dir = "OpsCore/vendor/%{prj.name}/"

		files{
			glfw_dir .. "include/GLFW/glfw3.h",
			glfw_dir .. "include/GLFW/glfw3native.h",
			glfw_dir .. "src/glfw_config.h",
			glfw_dir .. "src/context.c",
			glfw_dir .. "src/init.c",
			glfw_dir .. "src/input.c",
			glfw_dir .. "src/monitor.c",
			glfw_dir .. "src/vulkan.c",
			glfw_dir .. "src/window.c"
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
				glfw_dir .. "src/wgl_context.c",
				glfw_dir .. "src/egl_context.c",
				glfw_dir .. "src/osmesa_context.c"
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
			