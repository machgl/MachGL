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

    Window window("Mach::GL Game Engine Sandbox", WIDTH, HEIGHT);
    //window.vsync();

#if defined(FULLSCREEN)
    window.disableCursor();
    window.fullscreen();
#endif
    //window.debug();
    window.MSAA(8);
    window.init();
    
    Graphics::Image crosshairTexture("Textures/crosshair.png", Graphics::ImageType::RGBA, false);
    Graphics::Image grassTexture("Textures/grassBlock.jpg", Graphics::ImageType::RGB);
    Graphics::Image deathstarTexture("Textures/deathstar.png", Graphics::ImageType::RGB);
    Graphics::Image dirtTexture("Textures/dirtTexture.jpg", Graphics::ImageType::RGB);
    Graphics::Image aTexture("Textures/a.png", Graphics::ImageType::RGB);
        
    Plane::SimpleRect crosshair(float2((WIDTH / 2) - 25, (HEIGHT / 2) - 25), float2(50, 50), crosshairTexture.ref(), window.getWindowDimension());

    std::vector<std::string> fileNames {

        "Textures/Skybox/right.jpg",
        "Textures/Skybox/left.jpg",
        "Textures/Skybox/top.jpg",
        "Textures/Skybox/bottom.jpg",
        "Textures/Skybox/front.jpg",
        "Textures/Skybox/back.jpg"
    };

    std::vector<std::string> nightFileNames {

        "Textures/Skybox/nightRight.png",
        "Textures/Skybox/nightLeft.png",
        "Textures/Skybox/nightTop.png",
        "Textures/Skybox/nightBottom.png",
        "Textures/Skybox/nightFront.png",
        "Textures/Skybox/nightBack.png"
    };

    Graphics::Image skyboxTexture(fileNames);
    Graphics::Image nightSkyboxTexture(nightFileNames);

    Object::Skybox skybox(skyboxTexture.ref(), nightSkyboxTexture.ref());
    
    Graphics::Shader shader("Shaders/test.vert", "Shaders/test.frag");

    Object::Camera camera(float3(0, 5, 10), Object::CameraType::FPS, window.ref());
    
    Object::Light light(float3(10, 10, 10), float4(0, 0, 1, 1));
    Object::Light sun(float3(0, 70, 0), float4(1, 1, 0.8f, 1));

    light.setAttenuation(float3(1, 0.001f, 0.002f));
    sun.setBrightness(1.0f);
    
    std::vector<Object::Light> lights;

    //lights.push_back(light);
    lights.push_back(sun);
    
    Object::Model sphereModel("Models/sphere.obj");
    Object::Model suzanneModel("Models/suzanne.obj");
    Object::Model cubeModel("Models/cube.obj");
    Object::Model shipModel("Models/ship.obj");
    
    Object::Terrain terrain(800, 50, 2.5f, 1, 1.5f, 1);

    Object::Object scene(terrain.getModel(), float3(-200, 0, -200), dirtTexture.ref(), nullptr, Object::ObjectType::TERRAIN);
    Object::Object sun_object(sphereModel.ref(), sun.getPosition(), deathstarTexture.ref());
    Object::Object suzanne(suzanneModel.ref(), light.getPosition(), deathstarTexture.ref());
    Object::Object ship(cubeModel.ref(), float3(-10, 10, 10), nullptr);

    Object::ObjectProperties sunProperties;
    sunProperties.color = sun.getColor();

    Object::ObjectProperties sceneProperties;
    sceneProperties.shineDamper = 20;
    sceneProperties.reflectivity = 0.01f;
    sceneProperties.textureScale = 40;
    sceneProperties.scale = float3(2);

    Object::ObjectProperties suzanneProperties;
    suzanneProperties.color = light.getColor();
    suzanneProperties.shineDamper = 5;
    suzanneProperties.reflectivity = 0.4f;
    suzanneProperties.scale = float3(5);

    Object::ObjectProperties shipProperties;
    shipProperties.reflectivity = 0.4f;
    shipProperties.shineDamper = 5;
    
    Object::ObjectProperties cubeProperties;
    cubeProperties.shineDamper = 10;
    cubeProperties.reflectivity = 0.01f;

    std::vector<Object::Object> objects;
    std::vector<Object::Object> cubeObjects;

    uint32_t cubes = 8;

    for (uint32_t x = 0; x < cubes; x++) {
        for (uint32_t y = 0; y < cubes; y++) {
            for (uint32_t z = 0; z < cubes; z++) {

                Object::Object cube(cubeModel.ref(), float3(x * 10, y * 10, z * 10), grassTexture.ref());
                cube.create(cubeProperties);
                cubeObjects.push_back(cube);
            }
        }
    }

    scene.create(sceneProperties);
    sun_object.create(sunProperties);
    suzanne.create(suzanneProperties);
    ship.create(shipProperties);

    Graphics::EnvironmentMap enviroMap(1280, window.getWindowDimension());

    suzanne.setEnviromentMap(skybox.getObject()->getTID());
    ship.setEnviromentMap(enviroMap.getEnvironmentMap());
    
    objects.push_back(scene);
    objects.push_back(ship);
    objects.push_back(sun_object);
    objects.push_back(suzanne);
    
    Graphics::Renderer3D renderer3D;
    Graphics::Renderer3D renderer3D_2;
    matrix4x4 projection = Maths::Matrix::perspective(90, window.getWindowDimension(), 0.1f, 1000);
    matrix4x4 simpleProject = Maths::Matrix::simpleOrthographic(window.getWindowDimension());

    Timer fpsTimer;

    float angle = 0;
    float lastTime = 0;

    uint32_t framebufferScale = 1;

    Object::Camera enviroCamera(ship.getPosition(), Object::CameraType::CUBEMAP, window.ref());
    
    Object::Skybox enviroSkybox(enviroMap.getEnvironmentMap());

    std::vector<Object::Object> reflectedObjects;
    reflectedObjects.push_back(scene);
    reflectedObjects.push_back(suzanne);

    Graphics::HDR hdr(window.getWindowDimension());
    hdr.setExposure(1.4f);
    hdr.setGamma(1.3f);

    ship.setEnviromentMap(enviroMap.getEnvironmentMap());

    while (!window.closed()) {
        
        Timer time;

        window.clear();
        
        if (window.isWindowLoaded()) {

            float velocity = 0.5f * lastTime;

            camera.mouseMovement(0.3f);

            if (window.isKeyPressed(GLFW_KEY_ESCAPE)) MACH_CLOSE();
            if (window.isKeyPressed(GLFW_KEY_W)) camera.moveX(velocity);
            if (window.isKeyPressed(GLFW_KEY_S)) camera.moveX(-velocity);
            if (window.isKeyPressed(GLFW_KEY_D)) camera.moveZ(velocity);
            if (window.isKeyPressed(GLFW_KEY_A)) camera.moveZ(-velocity);
            if (window.isKeyPressed(GLFW_KEY_SPACE)) camera.moveY(velocity);
            if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) camera.moveY(-velocity);
            if (window.isKeyPressed(GLFW_KEY_P)) camera.reset();
            
            time.reset();

            enviroMap.capture();
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

            enviroMap.reflectedObjects(reflectedObjects, enviroCamera, shader.ref());

            shader.disable();
            enviroMap.stop();

            //****************************************************************************************
            
            
            
            //**************************************************************************************
            
            // Things for HDR 
            
            //****************************************************************************************************
            window.clear();
            
            hdr.capture();
            
            
            
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
            
            shader.setUniform1i("_texture", cubeObjects[0].getTID());
            shader.setUniformMatrix4fv("_pr_matrix", projection);
            shader.setUniformMatrix4fv("_vw_matrix", camera.getViewMatrix());
            shader.setUniform3f("_camera_position", camera.getPosition());
            
            renderer3D.submit(cubeObjects);
            
            shader.disable();
            
            for (int i = 0; i < objects.size(); i++) {
            
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
            
                shader.setUniform1i("_texture", objects[i].getTID());
                shader.setUniformMatrix4fv("_pr_matrix", projection);
                shader.setUniformMatrix4fv("_vw_matrix", camera.getViewMatrix());
                shader.setUniform3f("_camera_position", camera.getPosition());
                shader.setUniformMatrix4fv("_tr_matrix", matrix4x4(1));
            
                shader.setUniform1i("_environmentMap", objects[i].getEnvironmentMap());
            
                renderer3D.submit(objects[i]);
            
                shader.disable();
            }
            
            enviroSkybox.render(projection, camera.getViewMatrix());
            crosshair.render();
            
            hdr.stop();

            window.clear();

            hdr.render();

            //****************************************************************************************************
            
            fpsTimer.getFPS();
        }

        window.update();
        time.~Timer();
        lastTime = time.elapsedTimeMilliseconds() / 50;
    }

    scene.destroy();
    sun_object.destroy();
    suzanne.destroy();
    ship.destroy();

    window.~Window();

    return 0;
}
