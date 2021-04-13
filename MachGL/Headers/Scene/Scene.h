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

namespace MachGL {
	namespace Scene {

		class Scene {

			private:
				std::vector<Object::Object> m_objects;
				std::string m_filepath;
				Graphics::Renderer3D m_renderer;
				

			public:
				Scene(const std::string& filepath);
				void renderScene();

			private:
				void loadScene(const std::string& filepath);
		};
	}
}
