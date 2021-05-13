project "SimplexNoise"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    
    targetdir ("bin/" ..outputdir .. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir .. "/%{prj.name}")

    files
    {
        "include/SimplexNoise.h",
        "src/SimplexNoise.cpp"
    }

    includedirs
    {
        "include"
    }
    
    filter "system:windows"
        systemversion "latest"

    filter "system:macosx"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"