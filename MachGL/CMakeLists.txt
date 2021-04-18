#####################################################################################################################################

# NO NEED TO MODIFY (Unless adding/changing code that either changes file path to a particluar .cpp file or adding external projects)

cmake_minimum_required(VERSION 3.8.0)
add_subdirectory("Vendor/glfw")
add_subdirectory("Vendor/yaml-cpp")
add_library(MachGL
			"Source/Core/Window.cpp"
			"Source/Graphics/EnvironmentMap.cpp"
			"Source/Graphics/Framebuffer.cpp"
			"Source/Graphics/Image.cpp"
			"Source/Graphics/PostEffect.cpp"
			"Source/Graphics/Renderer2D.cpp"
			"Source/Graphics/Renderer3D.cpp"
			"Source/Graphics/SoftwareRender.cpp"
			"Source/Graphics/Shader.cpp"
			"Source/Object/Camera.cpp"
			"Source/Object/Model.cpp"
			"Source/Object/Object.cpp"
			"Source/Object/Skybox.cpp"
			"Source/Object/Terrain.cpp"
			"Source/Particle/ParticleCluster.cpp"
			"Source/Particle/QuadParticle.cpp"
			"Source/Plane/Plane.cpp"
			"Source/Plane/SimpleRect.cpp"
			"Source/Plane/SimpleTriangle.cpp"
			"Source/Screens/Splash.cpp"
			"Vendor/SimplexNoise.cpp")
include_directories(${YAML_CPP_SOURCE_DIR}/include)
if (APPLE)
	target_compile_options(MachGL PUBLIC "-Wno-deprecated-declarations")
endif()
target_include_directories(MachGL PUBLIC $(CMAKE_INCLUDE_CURRENT_DIR))

#####################################################################################################################################
