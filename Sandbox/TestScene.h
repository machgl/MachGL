#pragma once

#include "../MachGL/MachGL.h"

using namespace MachGL;

namespace Sandbox {

	class TestScene {

		private:
			MACH_WINDOW m_window;
			
			Scene::MACH_SCENE m_scene;
			Scene::MACH_GROUP m_mainGroup;

			Graphics::MACH_IMAGE m_grassTexture;
			Graphics::MACH_IMAGE m_dirtTexture;
			Graphics::MACH_IMAGE m_skyboxTexture;
			Graphics::MACH_IMAGE m_crosshairTexture;
			
			Graphics::MACH_SHADER m_shader;
			Graphics::MACH_ENVIRONMENT_MAP m_enviroMap;
			Object::MACH_CAMERA m_camera;
			Object::MACH_CAMERA m_enviroCamera;
			
			Object::MACH_MODEL m_cubeModel;
			Object::MACH_MODEL m_shipModel;
			
			Object::ObjectProperties m_cubeProperties;
			Object::ObjectProperties m_terrainProperties;
			Object::ObjectProperties m_shipProperties;
			Plane::RectProperties m_crosshairProperties;

			std::vector<Object::MACH_OBJECT> m_cubes;
			std::vector<Object::MACH_OBJECT> m_reflectedObjects;

			Object::MACH_SKYBOX m_skybox;
			Object::MACH_OBJECT m_terrain;
			Object::MACH_OBJECT m_ship;

			Plane::SimpleRect m_crosshair;
			matrix4x4 m_projection;

			std::vector<std::string> m_skyboxFileNames {

				"Textures/Skybox/right.jpg",
				"Textures/Skybox/left.jpg",
				"Textures/Skybox/top.jpg",
				"Textures/Skybox/bottom.jpg",
				"Textures/Skybox/front.jpg",
				"Textures/Skybox/back.jpg"
			};

		public:
			TestScene(const MACH_WINDOW& window, const Object::MACH_CAMERA& camera);
			~TestScene();
			void render();

		private:
			void init();
	};
}

