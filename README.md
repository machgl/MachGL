Mach::GL is an OpenGL game engine that combines the ease of high-level programming with the control of low level access. 

## How to install: 

- For all platforms ensure you have git installed.

#### Windows (Support for VS 2019 only):

- Create a directorary and navigate to it using: `cd path_to_directory`.
- Run the command (INCLUDE the dot at the end) `git clone https://github.com/machgl/MachGL .` (Note this will not clone some required modules - see next command).
- Run the command `git submodule update --init --remote`.
- Within the working directorary double-click on the windows_build_vs2019.bat file. This will make a VS solution file which can be opened.
- Once VS is open, right click on the 'Sandbox' project and select 'Set Default Startup Project'.
- Build the solution.

#### MacOS (Support for XCode only):

- Create a directorary and navigate to it using: `cd path_to_directory`.
- Run the command (INCLUDE the dot at the end) `git clone https://github.com/machgl/MachGL .` (Note this will not some required modules - see next command).
- Run the command `git submodule update --init --remote` to clone the required modules from third-party vendors.
- Run the command `./macos_build_xcode.sh` to build the xcode workspace.
- Open the generated XCode workspace file and navigate in the menu bar to Product -> Scheme and click on sandbox. 
- Build the solution.

##### Note (MacOS Only) 
Once the solution has been built, the 'CoreAssets' folder in MachGL must be copied into the build directory (To be fixed).

### Current features:
  - High performance 2D & 3D renderers
  - Framebuffers
  - OBJ file loading 
  - Texture mipmapping and anisotropic filtering
  - Random terrain generation
  - Keyboard & mouse input
  - GLSL shader loaders
  - HDR
  - Static environment maps for objects (from loaded cubemap)
  - Dynamic skyboxes 
  - API Abstraction
  
 ### Currently working on: 
  - Particle system
  - Texture atlases 
  - Documenting code
  - Dynamic enviornment maps for objects
  - Post-processing effects (bloom effects etc.)
  - Scene file saving/loading (using YAML)
  
 ### Features I want to add soon:
  - Scene editor
  - Mesh simplifier 
  - Normal maps
  - Shadows
  - Lua scripting
  - FBX file loading (for faster 3D object loading)
  - OpenAL support 
  - 3D physics using PhysX (including a non-nVidia alternative) 
  - Vulkan support
 
If you have any questions or issues feel free to file an issue on this GitHub page or email me at: james@mach-gl.com 
