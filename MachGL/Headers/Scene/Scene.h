/*

Mach::GL (Alpha)

*/

#pragma once

#include "MachPCH.h"
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
#include "Group.h"

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
			Graphics::MACH_SHADER shader;
			Graphics::MACH_IMAGE loadedTexture;
		};

		class Scene {

			private:
				std::vector<Object::MACH_OBJECT> m_objects;
				std::vector<Object::Light> m_lights;
				std::vector<SceneObject> m_sceneObjects;
				std::vector<MACH_GROUP> m_groups;
				std::string m_filepath;
				Graphics::MACH_RENDERER_3D m_renderer;
				std::vector<std::future<void>> m_futures;
				std::string m_sceneName;
				Object::MACH_SKYBOX m_skybox = nullptr;
				Object::MACH_CAMERA m_camera;
				matrix4x4 m_projection;

			public:
				Scene() = default;
				~Scene() = default;
				Scene(const std::string& filepath);
				Scene(const matrix4x4& projection, const Object::MACH_CAMERA& camera);
				void renderScene();
				inline void setSkybox(const Object::MACH_SKYBOX& skybox) { m_skybox = skybox; }
				inline void pushObject(const Object::MACH_OBJECT& object) { m_objects.push_back(object); }
				inline void pushGroup(const MACH_GROUP& group) { m_groups.push_back(group); }

				static sPoint<Scene> createScene(const std::string& filepath);
				static sPoint<Scene> createScene(const matrix4x4& projection, const Object::MACH_CAMERA& camera);

			private:
				void loadScene();
				void loadShader(const uint32_t& objectID);
				void unloadShader(const uint32_t& objectID);
		};

		using MACH_SCENE = sPoint<Scene>;
	}
}
