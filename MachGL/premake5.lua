project "MachGL"
    kind "StaticLib"
    language "C++"
    
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "Headers/**.h",
        "Source/**.cpp"
    }

    defines 
    {
        "GLFW_INCLUDE_NONE"
    }

    includedirs 
    {
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.yaml_cpp}",
        "%{IncludeDir.SimpleNoise}"
    }

    links 
    {
        "GLFW",
        "Glad",
        "yaml-cpp",
        "SimplexNoise"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        links
        {
            "opengl32.lib"
        }

    filter "system:linux"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

    filter "system:macosx"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        links
        {
            "OpenGL.framework",
            "Cocoa.framework",
            "IOKit.framework"
        }

    filter "configurations:Debug"
        defines "MACH_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "MACH_RELEASE"
        runtime "Release"
        optimize "On"