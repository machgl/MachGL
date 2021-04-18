//#define FULLSCREEN

#if defined(FULLSCREEN)

    #define WIDTH (float) 3840
    #define HEIGHT (float) 2160

#else
    #define WIDTH (float) 1280
    #define HEIGHT (float) 720
#endif

#define MAX_LIGHTS 12

#include "../MachGL/MachGL.h"

using namespace MachGL;

int main() {

    Window window("Mach::GL Game Engine Sandbox", WIDTH, HEIGHT);
    window.vsync();

#if defined(FULLSCREEN)
    window.disableCursor();
    window.fullscreen();
#endif
    //window.debug();
    //window.MSAA(2);
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
    
    Graphics::Shader shader("Sandbox/Shaders/test.vert", "Sandbox/Shaders/test.frag");

    Object::Camera camera(float3(0, 5, 10), Object::CameraType::FPS, window.ref());
    
    Object::Light light(float3(10, 10, 10), float4(0, 0, 1, 1));
    Object::Light sun(float3(0, 70, 0), float4(1, 1, 0.8f, 1));

    light.setAttenuation(float3(1, 0.001f, 0.002f));
    sun.setBrightness(1.0f);
    
    std::vector<Object::Light> lights;

    //lights.push_back(light);
    lights.push_back(sun);
    
    Object::Model sphereModel("Sandbox/Models/sphere.obj");
    Object::Model suzanneModel("Sandbox/Models/suzanne.obj");
    Object::Model cubeModel("Sandbox/Models/cube.obj");
    Object::Model shipModel("Sandbox/Models/ship.obj");
    
    Object::Terrain terrain(800, 50, 2.5f, 1, 1.5f, 1);

    Object::Object scene(terrain.getModel(), float3(-200, 0, -200), dirtTexture.ref(), nullptr, Object::ObjectType::TERRAIN);
    Object::Object sun_object(sphereModel.ref(), sun.getPosition(), deathstarTexture.ref());
    Object::Object suzanne(suzanneModel.ref(), light.getPosition(), deathstarTexture.ref());
    Object::Object cube(cubeModel.ref(), float3(0, 5, 10), grassTexture.ref());
    Object::Object ship(shipModel.ref(), float3(-10, 10, -10), nullptr);
    sun_object.setColor(sun.getColor());
    
    scene.setShineDamper(20);
    scene.setReflectivity(0.01f);
    scene.setTextureScale(40);
    scene.setScale(float3(2));
    
    suzanne.setColor(light.getColor());
    suzanne.setShineDamper(5);
    suzanne.setReflectivity(0.4f);

    suzanne.setScale(float3(5, 5, 5));
    ship.setReflectivity(0.4f);
    ship.setShineDamper(5);

    std::vector<Object::Object> objects;
    std::vector<Object::Object> cubeList;
    
    uint32_t cubes = 8;

    for (uint32_t x = 0; x < cubes; x++) {
        for (uint32_t y = 0; y < cubes; y++) {
            for (uint32_t z = 0; z < cubes; z++) {

                Object::Object cube(cubeModel.ref(), float3(x * 10, y * 10, z * 10), grassTexture.ref());
                cube.setShineDamper(10);
                cube.setReflectivity(0.01f);
                cube.create();
                cubeList.push_back(cube);
            }
        }
    }

    scene.create();
    sun_object.create();
    suzanne.create();
    ship.create();

    objects.push_back(scene);
    objects.push_back(ship);
    objects.push_back(sun_object);
    objects.push_back(cube);
    objects.push_back(suzanne);
    
    Graphics::Renderer3D renderer3D;
    Graphics::Renderer3D renderer3D_2;
    matrix4x4 projection = Maths::Matrix::perspective(90, window.getWindowDimension(), 0.1f, 1000);
    matrix4x4 simpleProject = Maths::Matrix::simpleOrthographic(window.getWindowDimension());

    Timer fpsTimer;

    float angle = 0;
    float lastTime = 0;

    uint32_t framebufferScale = 1;

    //Graphics::Framebuffer fb(WIDTH / framebufferScale, HEIGHT / framebufferScale);
    //Graphics::Image fbTexture(fb.getColorTexture());
    //Plane::SimpleRect framebufferQuad(float2(0, 0), float2(WIDTH / 2, HEIGHT / 2), fbTexture.ref(), window.getWindowDimension());

    Object::Camera enviroCamera(suzanne.getPosition(), Object::CameraType::CUBEMAP, window.ref());
    Graphics::EnvironmentMap enviroMap(128, window.getWindowDimension());

    std::vector<Object::Object> reflectedObjects;
    reflectedObjects.push_back(scene);

    Graphics::HDR hdr(window.getWindowDimension());
    hdr.setExposure(1.4f);
    hdr.setGamma(1.3f);

    while (!window.closed()) {
        
        Timer time;

        window.clear();
        
        if (window.isWindowLoaded()) {

            float velocity = 0.5f * lastTime;
            
            time.reset();

//            ****************************************************************************************
            
            enviroMap.capture();
            shader.enable();
            
            for (uint32_t i = 0; i < MAX_LIGHTS; i++) {
            
                std::string lightColor = "_light_color[" + std::to_string(i) + "]";
                std::string lightPos = "_light_position[" + std::to_string(i) + "]";
                std::string lightAttenuation = "_light_attenuation[" + std::to_string(i) + "]";
                std::string lightBrightness = "_light_brightness[" + std::to_string(i) + "]";
            
                if (i < lights.size()) {
            
                    shader.setUniform(lightColor.c_str(), lights[i].getColor());
                    shader.setUniform(lightPos.c_str(), lights[i].getPosition());
                    shader.setUniform(lightAttenuation.c_str(), lights[i].getAttenuation());
                    shader.setUniform(lightBrightness.c_str(), lights[i].getBrightness());
            
                }
                else {
            
                    shader.setUniform(lightColor.c_str(), float4(0, 0, 0, 0));
                    shader.setUniform(lightPos.c_str(), float3(0, 0, 0));
                    shader.setUniform(lightAttenuation.c_str(), float3(1, 0, 0));
                    shader.setUniform(lightBrightness.c_str(), 0.0f);
                }
            }
            
            shader.setUniform("_texture", scene.getTID());
            shader.setUniform("_pr_matrix", enviroCamera.getViewMatrix());
            shader.setUniform("_camera_position", enviroCamera.getPosition());
            
            enviroMap.reflectedObjects(reflectedObjects, enviroCamera);
            
            shader.disable();
            enviroMap.stop();

            //**************************************************************************************
            
            // Things for HDR 

            //****************************************************************************************************
            window.clear();

            hdr.capture();

            camera.mouseMovement(0.3f);
            
            ship.setEnviromentMap(skybox.getObject()->getTID());
            
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
            
                    shader.setUniform(lightColor.c_str(), lights[i].getColor());
                    shader.setUniform(lightPos.c_str(), lights[i].getPosition());
                    shader.setUniform(lightAttenuation.c_str(), lights[i].getAttenuation());
                    shader.setUniform(lightBrightness.c_str(), lights[i].getBrightness());
            
                }
                else {
            
                    shader.setUniform(lightColor.c_str(), float4(0, 0, 0, 0));
                    shader.setUniform(lightPos.c_str(), float3(0, 0, 0));
                    shader.setUniform(lightAttenuation.c_str(), float3(1, 0, 0));
                    shader.setUniform(lightBrightness.c_str(), 0.0f);
                }
            }
            
            shader.setUniform("_texture", cubeList[0].getTID());
            shader.setUniform("_pr_matrix", projection);
            shader.setUniform("_vw_matrix", camera.getViewMatrix());
            shader.setUniform("_camera_position", camera.getPosition());
            shader.setUniform("_environmentMap", (GLuint)ship.getEnvironmentMap());
            
            renderer3D.submit(cubeList);
            
            shader.disable();
            
            for (int i = 0; i < objects.size(); i++) {
            
                shader.enable();
            
                for (uint32_t i = 0; i < MAX_LIGHTS; i++) {
            
                    std::string lightColor = "_light_color[" + std::to_string(i) + "]";
                    std::string lightPos = "_light_position[" + std::to_string(i) + "]";
                    std::string lightAttenuation = "_light_attenuation[" + std::to_string(i) + "]";
                    std::string lightBrightness = "_light_brightness[" + std::to_string(i) + "]";
            
                    if (i < lights.size()) {
            
                        shader.setUniform(lightColor.c_str(), lights[i].getColor());
                        shader.setUniform(lightPos.c_str(), lights[i].getPosition());
                        shader.setUniform(lightAttenuation.c_str(), lights[i].getAttenuation());
                        shader.setUniform(lightBrightness.c_str(), lights[i].getBrightness());
            
                    }
                    else {
            
                        shader.setUniform(lightColor.c_str(), float4(0, 0, 0, 0));
                        shader.setUniform(lightPos.c_str(), float3(0, 0, 0));
                        shader.setUniform(lightAttenuation.c_str(), float3(1, 0, 0));
                        shader.setUniform(lightBrightness.c_str(), 0.0f);
                    }
                }
            
                shader.setUniform("_texture", objects[i].getTID());
                shader.setUniform("_pr_matrix", projection);
                shader.setUniform("_vw_matrix", camera.getViewMatrix());
                shader.setUniform("_camera_position", camera.getPosition());
            
                if (objects[i].getObjectID() != suzanne.getObjectID()) {
            
                    shader.setUniform("_environmentMap", enviroMap.getEnvironmentMap());
                }
                else {
            
                    shader.setUniform("_environmentMap", (GLuint)ship.getEnvironmentMap());
                }
            
                renderer3D.submit(objects[i]);
            
                shader.disable();
            }
            
            skybox.render(projection, camera.getViewMatrix());
            //framebufferQuad.render();
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
    cube.destroy();
    ship.destroy();

    window.~Window();

    return 0;
}
