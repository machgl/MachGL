project "MachGL"
    kind "StaticLib"
    language "C++"
    staticruntime "off"
    
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    --pchheader "MachPCH.h"
    --pchsource "MachPCH.cpp"

    files 
    {
        "**.h",
        "**.hpp",
        "MachPCH.cpp",
        "Headers/**.h",
        "Source/**.cpp"
    }
        
    defines 
    {
        "GLFW_INCLUDE_NONE",
        "_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS"
    }

    includedirs 
    {
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.yaml_cpp}",
        "%{IncludeDir.SimpleNoise}",
        "%{IncludeDir.Vulkan}",
        "%{wks.location}/MachGL/Vendor/glm"
    }

    links 
    {
        "GLFW",
        "Glad",
        "yaml-cpp",
        "SimplexNoise"
    }

    --flags { "NoPCH" }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        links
        {
            "opengl32.lib",
            "%{wks.location}/MachGL/Vendor/Vulkan/Lib/vulkan-1.lib"
        }

    filter "system:linux"
        cppdialect "C++17"
        systemversion "latest"

    filter "system:macosx"
        cppdialect "C++17"
        systemversion "latest"

    filter "configurations:Debug"
        defines "MACH_DEBUG"
        runtime "Debug"
        symbols "On"

        links 
        {
            "%{wks.location}/MachGL/Vendor/Vulkan/Lib/spirv-cross-cored.lib",
            "%{wks.location}/MachGL/Vendor/Vulkan/Lib/shaderc_shared.lib",
            "%{wks.location}/MachGL/Vendor/Vulkan/Lib/spirv-cross-glsld.lib",
            "%{wks.location}/MachGL/Vendor/Vulkan/Lib/spirv-Toolsd.lib"
        }

    filter "configurations:Release"
        defines "MACH_RELEASE"
        runtime "Release"
        optimize "On"

        links
        {
            "%{wks.location}/MachGL/Vendor/Vulkan/Lib/shaderc_shared.lib",
            "%{wks.location}/MachGL/Vendor/Vulkan/Lib/spirv-cross-core.lib",
            "%{wks.location}/MachGL/Vendor/Vulkan/Lib/spirv-cross-glsl.lib",
            "%{wks.location}/MachGL/Vendor/Vulkan/Lib/spirv-Tools.lib"
        }
