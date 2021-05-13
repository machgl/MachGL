project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"
    
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "**.h",
        "**.cpp"
    }

    includedirs 
    {
        "%{wks.location}/MachGL/Vendor/yaml-cpp/include"
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