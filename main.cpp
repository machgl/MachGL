#include "MachGL.h"

using namespace MachGL;

#define WIDTH (float) 1920
#define HEIGHT (float) 1080
#define MAX_LIGHTS 12

int main() {

    Window window("Kepler Game Engine", WIDTH, HEIGHT);
    //window.vsync();
    window.MSAA(8);
    //window.disableCursor();
    //window.fullscreen();
    //window.debug();
    window.init();

    Graphics::Image crosshair_texture("Textures/crosshair.png");
    Graphics::Image grassTexture("Textures/testTexture.jpg");
    Graphics::Image deathstarTexture("Textures/deathstar.png");
    Graphics::Image dirtTexture("Textures/dirtTexture.jpg");
    Graphics::SimpleRect simple(float2((WIDTH / 2) - 25, (HEIGHT / 2) - 25), float2(50, 50), &crosshair_texture, WIDTH, HEIGHT);
    

    std::vector<const char*> fileNames{

        "Textures/Skybox/right.jpg",
        "Textures/Skybox/left.jpg",
        "Textures/Skybox/bottom.jpg",
        "Textures/Skybox/top.jpg",
        "Textures/Skybox/front.jpg",
        "Textures/Skybox/back.jpg"
    };
    
    Graphics::Image skyboxTexture(fileNames);

    Object::Skybox skybox(&skyboxTexture);

    GLint m_TIDs[32] = {
                    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    };

    Graphics::Shader shader("test.vert", "test.frag");

    Object::Camera camera(float3(0, 5, 10), Object::CameraType::FPS, &window);

    Object::Light light(float3(10, 10, 10), float4(1, 1, 0, 1));
    Object::Light light2(float3(-10, 5, 10), float4(0, 1, 1, 1));
    Object::Light sun(float3(0, 70, 0), float4(1, 1, 0.8f, 1));

    light.setAttenuation(float3(1, 0.001f, 0.002f));
    light2.setAttenuation(float3(1, 0.003f, 0.002f));
    sun.setBrightness(0.4f);
    
    std::vector<Object::Light> lights;

    lights.push_back(light);
    lights.push_back(sun);
    lights.push_back(light2);

    Object::Model sphereModel("Models/sphere.obj");
    Object::Model suzanneModel("Models/suzanne.obj");
    Object::Model cubeModel("Models/cube.obj");
    Object::Model shipModel("Models/ship.obj");
    
    Object::Object scene(Object::Terrain(800, 70).getModel(), float3(-200, 0, -200), &dirtTexture);
    Object::Object sun_object(&sphereModel, sun.getPosition(), nullptr);
    Object::Object sphere(&sphereModel, light2.getPosition(), nullptr);
    Object::Object suzanne(&suzanneModel, light.getPosition(), &deathstarTexture);
    Object::Object cube(&cubeModel, float3(0, 5, 10), &grassTexture);
    Object::Object ship(&shipModel, float3(0, 15, 0), nullptr);

    sun_object.setColor(sun.getColor());
    
    scene.setShineDamper(20);
    scene.setReflectivity(0.01f);
    scene.setTextureScale(40);
    
    sphere.setColor(light.getColor());
    sphere.setShineDamper(5);
    sphere.setReflectivity(0.4f);
    
    suzanne.setColor(light2.getColor());
    suzanne.setShineDamper(5);
    suzanne.setReflectivity(0.4f);

    suzanne.setScale(float3(5, 5, 5));

    std::vector<Object::Object> objects;
    
    objects.push_back(scene);
    objects.push_back(sun_object);
    objects.push_back(sphere); 
    objects.push_back(suzanne);
    objects.push_back(cube);
    objects.push_back(ship);
    
    Graphics::Renderer3D renderer3D;
    matrix4x4 projection = Maths::Matrix::simpleProjection(90, WIDTH, HEIGHT);
    matrix4x4 simpleProject = Maths::Matrix::simpleOrthographic(WIDTH, HEIGHT);

    Timer fpsTimer;

    float angle = 0;
    double lastTime = 0;

    while (!window.closed()) {
        
        Timer time;

        window.clear();
        
        if (window.isWindowLoaded()) {

            float velocity = 0.5 * lastTime;
            camera.mouseMovement(0.3f);
            
            time.reset();

            matrix4x4 transform = matrix4x4(1.0);

            if (window.isKeyPressed(GLFW_KEY_ESCAPE)) MachGLClose();
            if (window.isKeyPressed(GLFW_KEY_W)) camera.moveX(velocity);
            if (window.isKeyPressed(GLFW_KEY_S)) camera.moveX(-velocity);
            if (window.isKeyPressed(GLFW_KEY_D)) camera.moveZ(velocity);
            if (window.isKeyPressed(GLFW_KEY_A)) camera.moveZ(-velocity);
            if (window.isKeyPressed(GLFW_KEY_SPACE)) camera.moveY(velocity);
            if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) camera.moveY(-velocity);
            if (window.isKeyPressed(GLFW_KEY_P)) camera.reset();
    
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
            shader.setUniformMatrix4fv("_vw_matrix", camera.getViewMatrix());

            renderer3D.submit(objects);

            shader.disable();
            
            skybox.render(projection, camera.getViewMatrix());

            simple.render();

            fpsTimer.getFPS();
        }

        window.update();
        
        time.~Timer();

        lastTime = time.elapsedTimeMilliseconds() / 50;
    }

    window.~Window();

    return 0;
}
