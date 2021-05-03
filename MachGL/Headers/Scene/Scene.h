/*

Mach::GL (Alpha)

*/

#pragma once

#include "../Core/Includes.h"
#include "../Utilities/Serializer.h"
#include "../Core/DataStructures.h"
#include "../Object/Object.h"
#include "../Graphics/Renderer3D.h"
#include "../Graphics/Image.h"
#include "../Graphics/Shader.h"
#include "../Object/Camera.h"
#include "../Object/Light.h"
#include "../Object/Skybox.h"
#include "../Object/Terrain.h"
#include "../Object/Model.h"

namespace MachGL {
	namespace Scene {
		
		static std::mutex m_objectLoaderMutex;

		struct SceneObject {

			uint32_t id;
			std::string mesh;
			float3 position;
			std::string texture;
			std::string vertShader;
			std::string fragShader;
			Object::ObjectProperties objectProperties;
			sPoint<Graphics::Shader> shader;
			sPoint<Graphics::Image> loadedTexture;
		};

		class Scene {

			private:
				std::vector<Object::Object> m_objects;
				std::vector<SceneObject> m_sceneObjects;
				std::string m_filepath;
				Graphics::Renderer3D m_renderer;
				std::vector<std::future<void>> m_futures;
				std::string m_sceneName;

			public:
				Scene(const std::string& filepath);
				void renderScene();

			private:
				void loadScene();
				void loadShader(const uint32_t& objectID);
				void unloadShader(const uint32_t& objectID);
		};
	}
}
