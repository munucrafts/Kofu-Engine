-- MoonlyEngine
workspace "MoonlyEngine"
	architecture "x64"
	startproject "MoonlyEngine"

	-- Force Visual Studio 2022 toolset toolset "v143"
	toolset "v143"
	
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

-- Include directories relative to MoonlyEngine
IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["Glad"] = "vendor/Glad/include"
IncludeDir["ImGui"] = "vendor/imgui"
IncludeDir["glm"] = "vendor/glm"
IncludeDir["stb_image"] = "vendor/stb_image"
IncludeDir["JsonParser"] = "vendor/JsonParser"
IncludeDir["tinygltf"] = "vendor/tinygltf"

-- Projects
group "Dependencies"
	include "MoonlyEngine/vendor/GLFW"
	include "MoonlyEngine/vendor/Glad"
	include "MoonlyEngine/vendor/imgui"
group ""

include "MoonlyEngine"
include "MoonlyEngine"