#include "TestScene.h"

namespace Sandbox {

	TestScene::TestScene(const MACH_WINDOW& window, const Object::MACH_CAMERA& camera) {

		m_window = window;
		m_skyboxTexture = Graphics::Image::createImage(m_skyboxFileNames);
		m_skybox = Object::Skybox::createSkybox(m_skyboxTexture);
		m_projection = Maths::Matrix::perspective(90, m_window->getWindowDimension(), 0.1f, 1000);
		m_scene = Scene::Scene::createScene(m_projection, camera);
		m_camera = camera;
		
		init();	
	}

	TestScene::~TestScene() {

		for (size_t i = 0; i < m_cubes.size(); i++) 
			m_cubes[i]->destroy();
		
		m_terrain->destroy();
	}

	void TestScene::init() {

		m_grassTexture = Graphics::Image::createImage("Textures/grassBlock.jpg", Graphics::ImageType::RGB);
		m_dirtTexture = Graphics::Image::createImage("Textures/dirtTexture.jpg", Graphics::ImageType::RGB);
		m_crosshairTexture = Graphics::Image::createImage("Textures/crosshair.png", Graphics::ImageType::RGBA, false);

		m_cubeModel = Object::Model::createModel("Models/cube.obj");
		m_shipModel = Object::Model::createModel("Models/sphere.obj");

		m_shader = Graphics::Shader::createShader("Shaders/test.mglsdr");
		m_mainGroup = Scene::Group::createGroup(m_shader, m_projection);
		
		m_terrain = Object::Object::createObject(Object::Terrain(800, 50, 2.5f, 1, 1.5f, 1).getModel(), float3(-200, 0, -200), m_dirtTexture, nullptr, Object::ObjectType::TERRAIN);
		m_ship = Object::Object::createObject(m_shipModel, float3(-10, 10, 10), nullptr);
		
		m_cubeProperties.shineDamper = 10;
		m_cubeProperties.reflectivity = 0.01f;

		m_terrainProperties.shineDamper = 20;
		m_terrainProperties.reflectivity = 0.01f;
		m_terrainProperties.textureScale = 40;
		m_terrainProperties.scale = float3(2);

		m_crosshairProperties.position = float2((m_window->getWidth() / 2) - 25, (m_window->getHeight() / 2) - 25);
		m_crosshairProperties.size = float2(50, 50);
		m_crosshairProperties.image = m_crosshairTexture;

		m_shipProperties.reflectivity = 0.7f;
		m_shipProperties.shineDamper = 2;

		m_terrain->create(m_terrainProperties);
		m_ship->create(m_shipProperties);
		m_scene->setSkybox(m_skybox);

		m_crosshair = Plane::SimpleRect(m_crosshairProperties, m_window->getWindowDimension());
		m_crosshair.create();

		m_enviroCamera = Object::Camera::createCamera(m_ship->getPosition(), Object::CameraType::CUBEMAP, m_window);
		m_enviroMap = Graphics::EnvironmentMap::createEnvironmentMap(1024, m_window->getWindowDimension());

		uint32_t cubes = 10;

		for (uint32_t x = 0; x < cubes; x++) {
			for (uint32_t y = 0; y < cubes; y++) {
				for (uint32_t z = 0; z < cubes; z++) {
		
					m_cubes.push_back(Object::Object::createObject(m_cubeModel, float3(x * 10, y * 10, z * 10), m_grassTexture));
				}
			}
		}
		
		for (uint32_t i = 0; i < m_cubes.size(); i++) {
		
			m_cubes[i]->create(m_cubeProperties);
			m_mainGroup->pushObject(m_cubes[i]);
		}

		m_mainGroup->pushObject(m_ship);
		m_mainGroup->pushObject(m_terrain);
		m_scene->pushGroup(m_mainGroup);

		m_reflectedObjects.push_back(m_terrain);
		m_reflectedObjects.insert(m_reflectedObjects.end(), m_cubes.begin(), m_cubes.end());

		m_enviroMap->capture();
		m_enviroMap->reflectedObjects(m_reflectedObjects, *m_enviroCamera, m_skybox);
		m_enviroMap->stop();

		m_ship->setEnviromentMap(m_enviroMap->getEnvironmentMap());
	}

	void TestScene::render() {

		m_scene->renderScene();
		m_crosshair.render();
	}
}