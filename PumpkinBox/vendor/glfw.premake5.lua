project "GLFW"
		kind "StaticLib"
		language "C"
		staticruntime "on"

		targetdir("../../bin/" .. outputdir .. "/%{prj.name}")
		objdir("../../bin-int/" .. outputdir .. "/%{prj.name}")

		glfw_dir = "GLFW/"

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
				glfw_dir .. "src/linux_joystick.c"
			}

			defines
			{
				"_GLFW_X11"
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