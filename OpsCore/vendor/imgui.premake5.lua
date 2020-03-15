project "ImGui"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("../../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../../bin-int/" .. outputdir .. "/%{prj.name}")

	imgui_dir = "imgui/"

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

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
