include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "MachGL" 
    architecture "x64"
    startproject "Sandbox"

    configurations {
        
        "Debug",
        "Release"
    }

    flags {

        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "MachGL/Vendor/glfw"
    include "MachGL/Vendor/Glad"
    include "MachGL/Vendor/yaml-cpp"
    include "MachGL/Vendor/SimplexNoise"
group ""

include "MachGL"
include "Sandbox"


    