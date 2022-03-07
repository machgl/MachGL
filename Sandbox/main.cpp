//#define FULLSCREEN

#if defined(FULLSCREEN)

    #define WIDTH (uint32_t) 3840
    #define HEIGHT (uint32_t) 2160

#else
    #define WIDTH (uint32_t) 1920
    #define HEIGHT (uint32_t) 1080
#endif

#define MAX_LIGHTS 12

#include "TestScene.h"
#include "../MachGL/MachGL.h"

using namespace MachGL;

int main() {

    MACH_WINDOW window = Window::createWindow("Sandbox", WIDTH, HEIGHT);
    //window->vsync();

#if defined(FULLSCREEN)
    window->disableCursor();
    window->fullscreen();
#endif
    //window->debug();
    window->MSAA(8);
    window->init();
  
    Graphics::HDR hdr(window->getWindowDimension());
    hdr.setExposure(1.4f);
    hdr.setGamma(1.3f);

    Timer fpsTimer;
    float lastTime = 0;

    Object::MACH_CAMERA camera = Object::Camera::createCamera(float3(0, 10, 0), Object::CameraType::FPS, window);
    Sandbox::TestScene testScene(window, camera);

    Audio::AudioFile testAudio("Audio/test.ogg");
    Audio::MACH_SOUND_BUFFER soundBuffer = Audio::SoundBuffer::createSoundBuffer();
    Audio::MACH_SOUND_SOURCE soundSource = Audio::SoundSource::createSoundSource();

    soundBuffer->addSoundEffect(testAudio);
    soundSource->play(testAudio.getBufferID());

    while (!window->closed()) {
        
        Timer time;

        window->clear();
        
        if (window->isWindowLoaded()) {

            float velocity = 0.5f * lastTime;

            camera->mouseMovement(0.3f);

            if (window->isKeyPressed(GLFW_KEY_ESCAPE)) MACH_CLOSE();
            if (window->isKeyPressed(GLFW_KEY_W)) camera->moveX(velocity);
            if (window->isKeyPressed(GLFW_KEY_S)) camera->moveX(-velocity);
            if (window->isKeyPressed(GLFW_KEY_D)) camera->moveZ(velocity);
            if (window->isKeyPressed(GLFW_KEY_A)) camera->moveZ(-velocity);
            if (window->isKeyPressed(GLFW_KEY_SPACE)) camera->moveY(velocity);
            if (window->isKeyPressed(GLFW_KEY_LEFT_SHIFT)) camera->moveY(-velocity);
            if (window->isKeyPressed(GLFW_KEY_P)) camera.reset();
            
            time.reset();

            window->clear();
            
            hdr.capture();
            
            testScene.render();
            
            hdr.stop();
            hdr.render();
            
            fpsTimer.getFPS();
        }

        window->update();
        time.~Timer();
        lastTime = time.elapsedTimeMilliseconds() / 50;
    }

    testScene.~TestScene();

    window->close();

    return 0;
}
