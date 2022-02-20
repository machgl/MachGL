/*

Mach::GL (Alpha)

*/

#include "../../Headers/Scene/Scene.h"

namespace MachGL {
	namespace Scene {

		Scene::Scene(const std::string& filepath) : m_filepath(filepath) {
			loadScene();
		}

		Scene::Scene(const matrix4x4& projection, const Object::MACH_CAMERA& camera) {

			m_renderer = Graphics::Renderer3D::createRenderer();
			m_projection = projection;
			m_camera = camera;
		}

		MACH_SCENE Scene::createScene(const std::string& filepath) {
			return make_sPoint<Scene>(filepath);
		}

		MACH_SCENE Scene::createScene(const matrix4x4& projection, const Object::MACH_CAMERA& camera) {
			return make_sPoint<Scene>(projection, camera);
		}

		void loadObject(const SceneObject& sceneObject, std::vector<Object::MACH_OBJECT>* objects) {

			sPoint<Object::Model> model = make_sPoint<Object::Model>(sceneObject.mesh);
			Object::MACH_OBJECT object = Object::Object::createObject(model, sceneObject.position, sceneObject.loadedTexture);

			object->create(sceneObject.objectProperties);

			std::lock_guard<std::mutex> lock(m_objectLoaderMutex);
			objects->push_back(object);
		}

		void Scene::loadScene() {

            m_renderer = Graphics::Renderer3D::createRenderer();
            
			if (m_filepath.substr(m_filepath.find_last_of(".") + 1) != "msf") {

				MACH_ERROR_MSG("File type not a MachGL scene file (.msf)");
				return;
			}

			YAML::Node data = YAML::LoadFile(m_filepath);

			if (!data["Scene"]) {

				MACH_ERROR_MSG(m_filepath + " is not a valid scene");
				return;
			}

			m_sceneName = data["Scene"].as<std::string>();

			YAML::Node objects = data["Objects"];

			if (objects) {
				for (auto object : objects) {

					SceneObject sceneObject;

					//Read from scene file 
					if (object["ID"]) sceneObject.id = object["ID"].as<uint32_t>();
					if (object["Mesh"]) sceneObject.mesh = object["Mesh"].as<std::string>();
					if (object["Position"]) sceneObject.position = object["Postion"].as<float3>();
					if (object["Texture"]) sceneObject.texture = object["Texture"].as<std::string>();
					if (object["VertexShader"]) sceneObject.vertShader = object["VertexShader"].as<std::string>();
					if (object["FragmentShader"]) sceneObject.fragShader = object["FragmentShader"].as<std::string>();
					if (object["ShineDamper"]) sceneObject.objectProperties.shineDamper = object["ShineDamper"].as<float>();
					if (object["Reflectivity"]) sceneObject.objectProperties.reflectivity = object["Reflectivity"].as<float>();
					if (object["TexttureScale"]) sceneObject.objectProperties.textureScale = object["TextureScale"].as<float>();
					if (object["Scale"]) sceneObject.objectProperties.scale = object["Scale"].as<float3>();
					if (object["Color"]) sceneObject.objectProperties.color = object["Color"].as<float4>();

					//Load in shaders and texture 
					if (object["VertexShader"] && object["FragmentShader"]) sceneObject.shader = Graphics::Shader::createShader(sceneObject.vertShader, sceneObject.fragShader);
					sceneObject.loadedTexture = object["texture"] ? Graphics::Image::createImage(sceneObject.texture, Graphics::ImageType::RGB) : nullptr;

					m_futures.push_back(std::async(std::launch::async, loadObject, sceneObject, &m_objects));
				}

				MACH_ERROR_MSG("Could not find any objects in: " + m_filepath);
			}

			MACH_MSG("Loaded scene: " + m_sceneName + " from " + m_filepath);
		}

		void Scene::loadShader(const uint32_t& objectID) {

			for (uint32_t i = 0; i < m_sceneObjects.size(); i++) {
				if (m_sceneObjects[i].id == objectID) {
					m_sceneObjects[i].shader->enable();
				}
			}
		}

		void Scene::unloadShader(const uint32_t& objectID) {

			for (uint32_t i = 0; i < m_sceneObjects.size(); i++) {
				if (m_sceneObjects[i].id == objectID) {
					m_sceneObjects[i].shader->disable();
				}
			}
		}

		void Scene::renderScene() {

			if (m_objects.size() > 0) {

				for (uint32_t i = 0; i < m_objects.size(); i++) {

					loadShader(m_objects[i]->getObjectID());
					m_renderer->submit(m_objects[i]);
					unloadShader(m_objects[i]->getObjectID());
				}
			}

			if (m_groups.size() > 0) {
				for (uint32_t i = 0; i < m_groups.size(); i++) {
			
					auto& objects = m_groups[i]->getObjects();
					m_groups[i]->getShader()->enable();
					m_groups[i]->getShader()->setUniform3f("_camera_position", m_camera->getPosition());
					m_groups[i]->getMatrixUBO()->setData(&m_camera->getViewMatrix(), sizeof(matrix4x4), sizeof(matrix4x4));

					for (uint32_t j = 0; j < objects.size(); j++)
						m_renderer->submit(objects[j]);
			
					m_groups[i]->getShader()->disable();
				}
			}

			if (m_skybox) m_skybox->render(m_projection, m_camera->getViewMatrix());
		}
	}
}
