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

		class Skybox {

			private:
				Graphics::Image* m_image;
				std::vector<float3> m_vertices;
				Graphics::Renderer3D m_renderer;
				std::vector<Object> m_objects;
				Object* m_object;
				Graphics::Shader* m_shader;
				std::vector<float3> makeVertices();
			public:
				Skybox(Graphics::Image* image);
				void render(const matrix4x4& projection, const matrix4x4& view);
		};
	}
}
