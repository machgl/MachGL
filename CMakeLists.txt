cmake_minimum_required(VERSION 3.4)
project(TestCompile)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory("MachGL")
find_package(OpenGL REQUIRED)

################################################################################

# Change the "Sandbox/main.cpp" to the path to your main.cpp file.
add_executable(TestCompile Sandbox/main.cpp)

################################################################################

target_link_libraries(TestCompile PRIVATE MachGL glfw OpenGL::GL yaml-cpp)