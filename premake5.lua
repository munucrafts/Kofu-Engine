-- KofuEngine
workspace "KofuEngine"
	architecture "x64"
	startproject "KofuEngine"

	-- Force Visual Studio 2026 toolset toolset "v145"
	toolset "v145"
	
	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to KofuEngine
IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["Glad"] = "vendor/Glad/include"
IncludeDir["ImGui"] = "vendor/imgui"
IncludeDir["glm"] = "vendor/glm"
IncludeDir["stb_image"] = "vendor/stb_image"
IncludeDir["JsonParser"] = "vendor/JsonParser"
IncludeDir["tinygltf"] = "vendor/tinygltf"
IncludeDir["OpenAL"] = "vendor/OpenAL/include"

-- Projects
group "Dependencies"
	include "KofuEngine/vendor/GLFW"
	include "KofuEngine/vendor/Glad"
	include "KofuEngine/vendor/imgui"
group ""

include "KofuEngine"