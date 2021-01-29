/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../../Headers/Core/Includes.h"
#include "../../Headers/Core/DataStructures.h"
#include "../../Headers/Graphics/Image.h"
#include "Model.h"
#include "Object.h"
#include "../../Headers/Graphics/Renderer3D.h"

namespace MachGL {
	namespace Object {

		class Skybox : public Object {

			private:
				Graphics::Image* m_image;
				std::vector<float3> m_vertices;
				Graphics::Renderer3D m_renderer;
				Model m_skyboxModel;
				std::vector<Object> m_objects;
				Graphics::Shader* m_shader;
				void init();
			public:
				Skybox(Graphics::Image* image);
				void render(const matrix4x4& projection, const matrix4x4& view);
		};
	}
}
