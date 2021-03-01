//#define FULLSCREEN

#if defined(FULLSCREEN)

    #define WIDTH (float) 3840
    #define HEIGHT (float) 2160

#else
    #define WIDTH (float) 1920
    #define HEIGHT (float) 1080
#endif

#define MAX_LIGHTS 12

#include "../MachGL/MachGL.h"

using namespace MachGL;

int main() {

    Window window("Kepler Game Engine", WIDTH, HEIGHT);
    //window.vsync();

#if defined(FULLSCREEN)
    window.disableCursor();
    window.fullscreen();
#endif
    //window.debug();
    window.MSAA(8);
    window.init();

    Graphics::Image crosshairTexture("Sandbox/Textures/crosshair.png", Graphics::ImageType::RGBA, false);
    Graphics::Image grassTexture("Sandbox/Textures/grassBlock.jpg", Graphics::ImageType::RGB);
    Graphics::Image deathstarTexture("Sandbox/Textures/deathstar.png", Graphics::ImageType::RGB);
    Graphics::Image dirtTexture("Sandbox/Textures/dirtTexture.jpg", Graphics::ImageType::RGB);
    Graphics::Image aTexture("Sandbox/Textures/a.png", Graphics::ImageType::RGB);
    
    Plane::SimpleRect crosshair(float2((WIDTH / 2) - 25, (HEIGHT / 2) - 25), float2(50, 50), crosshairTexture.ref(), window.getWindowDimension());

    std::vector<std::string> fileNames {

        "Sandbox/Textures/Skybox/right.jpg",
        "Sandbox/Textures/Skybox/left.jpg",
        "Sandbox/Textures/Skybox/bottom.jpg",
        "Sandbox/Textures/Skybox/top.jpg",
        "Sandbox/Textures/Skybox/front.jpg",
        "Sandbox/Textures/Skybox/back.jpg"
    };

    std::vector<std::string> nightFileNames {

        "Sandbox/Textures/Skybox/nightRight.png",
        "Sandbox/Textures/Skybox/nightLeft.png",
        "Sandbox/Textures/Skybox/nightBottom.png",
        "Sandbox/Textures/Skybox/nightTop.png",
        "Sandbox/Textures/Skybox/nightFront.png",
        "Sandbox/Textures/Skybox/nightBack.png"
    };

    Graphics::Image skyboxTexture(fileNames);
    Graphics::Image nightSkyboxTexture(nightFileNames);

    Object::Skybox skybox(skyboxTexture.ref(), nightSkyboxTexture.ref());
    
    GLint m_TIDs[32] = {
                    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    };

    Graphics::Shader shader("Sandbox/Shaders/test.vert", "Sandbox/Shaders/test.frag");

    Object::Camera camera(float3(0, 5, 10), Object::CameraType::FPS, window.ref());
    Object::Camera camera2(float3(0, 5, 10), Object::CameraType::FPS, window.ref());
    
    Object::Light light(float3(10, 10, 10), float4(0, 0, 1, 1));
    Object::Light sun(float3(0, 70, 0), float4(1, 1, 0.8f, 1));

    light.setAttenuation(float3(1, 0.001f, 0.002f));
    sun.setBrightness(1.0f);
    
    std::vector<Object::Light> lights;

    lights.push_back(light);
    lights.push_back(sun);
    
    Object::Model sphereModel("Sandbox/Models/sphere.obj");
    Object::Model suzanneModel("Sandbox/Models/suzanne.obj");
    Object::Model cubeModel("Sandbox/Models/cube.obj");
    Object::Model shipModel("Sandbox/Models/ship.obj");
    
    Object::Terrain terrain(800, 50, 2.5f, 1, 1.5f, 1);

    Object::Object scene(terrain.getModel(), float3(-200, 0, -200), dirtTexture.ref(), nullptr, Object::ObjectType::TERRAIN);
    Object::Object sun_object(sphereModel.ref(), sun.getPosition(), nullptr);
    Object::Object suzanne(suzanneModel.ref(), light.getPosition(), deathstarTexture.ref());
    Object::Object cube(cubeModel.ref(), float3(0, 5, 10), grassTexture.ref());
    Object::Object ship(shipModel.ref(), float3(0, 10, 0), nullptr);

    sun_object.setColor(sun.getColor());
    
    scene.setShineDamper(20);
    scene.setReflectivity(0.01f);
    scene.setTextureScale(40);
    scene.setScale(float3(2));
    
    suzanne.setColor(light.getColor());
    suzanne.setShineDamper(5);
    suzanne.setReflectivity(0.4f);

    suzanne.setScale(float3(5, 5, 5));

    std::vector<Object::Object> objects;
    
    uint32_t cubes = 10;

    for (uint32_t x = 0; x < cubes; x++) {
        for (uint32_t y = 0; y < cubes; y++) {
            for (uint32_t z = 0; z < cubes; z++) {

                Object::Object sphere(cubeModel.ref(), float3(x * 10, y * 10, z * 10), grassTexture.ref());
                sphere.create();
                objects.push_back(sphere);
            }
        }
    }

    scene.create();
    sun_object.create();
    suzanne.create();
    cube.create();
    ship.create();

    objects.push_back(scene);
    objects.push_back(sun_object);
    objects.push_back(suzanne);
    objects.push_back(cube);
    objects.push_back(ship);
    
    Graphics::Renderer3D renderer3D;
    Graphics::Renderer3D renderer3D_2;
    matrix4x4 projection = Maths::Matrix::projection(90, window.getWindowDimension(), 0.1f, 1000);
    matrix4x4 simpleProject = Maths::Matrix::simpleOrthographic(window.getWindowDimension());

    Timer fpsTimer;

    float angle = 0;
    float lastTime = 0;

    uint32_t framebufferScale = 1;

    Graphics::Framebuffer fb(WIDTH / framebufferScale, HEIGHT / framebufferScale);

    Graphics::Image fbTexture(fb.getColorTexture());

    Plane::SimpleRect framebufferQuad(float2(0, 0), float2(WIDTH / 2, HEIGHT / 2), fbTexture.ref(), window.getWindowDimension());

    while (!window.closed()) {
        
        Timer time;

        window.clear();
        
        if (window.isWindowLoaded()) {

            fb.capture();
            
            float velocity = 0.5f * lastTime;
            camera2.mouseMovement(0.3f);
            
            time.reset();
            
            matrix4x4 transform = matrix4x4(1.0);
            
            if (window.isKeyPressed(GLFW_KEY_ESCAPE)) MACH_CLOSE();
            if (window.isKeyPressed(GLFW_KEY_W)) camera2.moveX(velocity);
            if (window.isKeyPressed(GLFW_KEY_S)) camera2.moveX(-velocity);
            if (window.isKeyPressed(GLFW_KEY_D)) camera2.moveZ(velocity);
            if (window.isKeyPressed(GLFW_KEY_A)) camera2.moveZ(-velocity);
            if (window.isKeyPressed(GLFW_KEY_SPACE)) camera2.moveY(velocity);
            if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) camera2.moveY(-velocity);
            if (window.isKeyPressed(GLFW_KEY_P)) camera2.reset();
            
            shader.enable();
            
            for (int i = 0; i < MAX_LIGHTS; i++) {
            
                std::string lightColor = "_light_color[" + std::to_string(i) + "]";
                std::string lightPos = "_light_position[" + std::to_string(i) + "]";
                std::string lightAttenuation = "_light_attenuation[" + std::to_string(i) + "]";
                std::string lightBrightness = "_light_brightness[" + std::to_string(i) + "]";
            
                if (i < lights.size()) {
            
                    shader.setUniform4f(lightColor.c_str(), lights[i].getColor());
                    shader.setUniform3f(lightPos.c_str(), lights[i].getPosition());
                    shader.setUniform3f(lightAttenuation.c_str(), lights[i].getAttenuation());
                    shader.setUniform1f(lightBrightness.c_str(), lights[i].getBrightness());
                    
                } else {
            
                    shader.setUniform4f(lightColor.c_str(), float4(0, 0, 0, 0));
                    shader.setUniform3f(lightPos.c_str(), float3(0, 0, 0));
                    shader.setUniform3f(lightAttenuation.c_str(), float3(1, 0, 0));
                    shader.setUniform1f(lightBrightness.c_str(), 0.0f);
                }
            }
            
            shader.setUniform1iv("_TIDs", m_TIDs, 32);
            shader.setUniformMatrix4fv("_pr_matrix", projection);
            shader.setUniformMatrix4fv("_tr_matrix", transform);
            shader.setUniformMatrix4fv("_vw_matrix", camera2.getViewMatrix());
            
            renderer3D_2.submit(objects);
            
            shader.disable();
            
            skybox.render(projection, camera2.getViewMatrix());
            crosshair.render();
            
            fb.stop();

            window.clear();

            camera.mouseMovement(0.3f);

            if (window.isKeyPressed(GLFW_KEY_ESCAPE)) MACH_CLOSE();
            if (window.isKeyPressed(GLFW_KEY_W)) camera.moveX(velocity);
            if (window.isKeyPressed(GLFW_KEY_S)) camera.moveX(-velocity);
            if (window.isKeyPressed(GLFW_KEY_D)) camera.moveZ(velocity);
            if (window.isKeyPressed(GLFW_KEY_A)) camera.moveZ(-velocity);
            if (window.isKeyPressed(GLFW_KEY_SPACE)) camera.moveY(velocity);
            if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) camera.moveY(-velocity);
            if (window.isKeyPressed(GLFW_KEY_P)) camera.reset();

            shader.enable();

            for (uint32_t i = 0; i < MAX_LIGHTS; i++) {

                std::string lightColor = "_light_color[" + std::to_string(i) + "]";
                std::string lightPos = "_light_position[" + std::to_string(i) + "]";
                std::string lightAttenuation = "_light_attenuation[" + std::to_string(i) + "]";
                std::string lightBrightness = "_light_brightness[" + std::to_string(i) + "]";

                if (i < lights.size()) {

                    shader.setUniform4f(lightColor.c_str(), lights[i].getColor());
                    shader.setUniform3f(lightPos.c_str(), lights[i].getPosition());
                    shader.setUniform3f(lightAttenuation.c_str(), lights[i].getAttenuation());
                    shader.setUniform1f(lightBrightness.c_str(), lights[i].getBrightness());

                }
                else {

                    shader.setUniform4f(lightColor.c_str(), float4(0, 0, 0, 0));
                    shader.setUniform3f(lightPos.c_str(), float3(0, 0, 0));
                    shader.setUniform3f(lightAttenuation.c_str(), float3(1, 0, 0));
                    shader.setUniform1f(lightBrightness.c_str(), 0.0f);
                }
            }

            shader.setUniform1iv("_TIDs", m_TIDs, 32);
            shader.setUniformMatrix4fv("_pr_matrix", projection);
            shader.setUniformMatrix4fv("_tr_matrix", transform);
            shader.setUniformMatrix4fv("_vw_matrix", camera.getViewMatrix());

            renderer3D.submit(objects);

            shader.disable();

            skybox.render(projection, camera.getViewMatrix());
            framebufferQuad.render();
            crosshair.render();

            fpsTimer.getFPS();
        }

        window.update();
        time.~Timer();
        lastTime = time.elapsedTimeMilliseconds() / 50;
    }

    scene.destroy();
    sun_object.destroy();
    suzanne.destroy();
    cube.destroy();
    ship.destroy();

    window.~Window();

    return 0;
}
