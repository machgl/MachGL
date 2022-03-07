project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"
    
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "**.h",
        "**.cpp"
    }

    includedirs 
    {
        "%{wks.location}/MachGL/Vendor/yaml-cpp/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.yaml_cpp}",
        "%{IncludeDir.SimpleNoise}",
        "%{IncludeDir.Vulkan}",
        "%{IncludeDir.OpenAL_Soft1}",
        "%{IncludeDir.OpenAL_Soft2}",
        "%{IncludeDir.OpenAL_Soft3}",
        "%{IncludeDir.Vorbis}",
        "%{IncludeDir.libogg}",
        "%{IncludeDir.minimp3}"
    }

    defines 
    {
        "_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS"
    }

    links 
    {
        "MachGL"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

    filter "system:macosx"
        cppdialect "C++17"

        links
        {
            "OpenGL.framework",
            "Cocoa.framework",
            "IOKit.framework",
            "CoreVideo.framework"
        }

    filter "configurations:Debug"
        defines "MACH_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "MACH_RELEASE"
        runtime "Release"
        optimize "On"