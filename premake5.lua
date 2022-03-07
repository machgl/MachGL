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
    include "MachGL/Vendor/HazelAudio/HazelAudio/vendor/OpenAL-Soft"
    include "MachGL/Vendor/HazelAudio/HazelAudio/vendor/libogg"
    include "MachGL/Vendor/HazelAudio/HazelAudio/vendor/Vorbis"
group ""

include "MachGL"
include "Sandbox"
include "VulkanSandbox"


    