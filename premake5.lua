workspace "OpsCore"
	
	architecture "x64"
	
	configurations 
	{ 
		"Debug", 
		"Release", 
		"Dist" 
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	project "OpsCore"
		
		location "OpsCore"
		kind "SharedLib"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h", 
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"%{prj.name}/vendor/spdlog/include"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines
			{
				"OC_PLATFORM_WINDOWS",
				"OC_BUILD_DLL"
			}

			postbuildcommands
			{
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
			}

		filter "configurations:Debug"
			defines "OC_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "OC_RELEASE"
			symbols "On"
		
		filter "configurations:Dist"
			defines "OC_DIST"
			symbols "On"

	project "Sandbox"
		
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"

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
			"OpsCore/src"
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
			symbols "On"

		filter "configurations:Release"
			defines "OC_RELEASE"
			symbols "On"
		
		filter "configurations:Dist"
			defines "OC_DIST"
			symbols "On"
