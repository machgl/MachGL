/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"
#include "../Graphics/Image.h"
#include "Model.h"
#include "Object.h"
#include "../Graphics/Renderer3D.h"

namespace MachGL {
	namespace Object {

		enum class SkyboxType {

			STATIC, DYNAMIC
		};

		class Skybox {

			private:
				std::vector<float3> m_vertices;
				Graphics::Renderer3D m_renderer;
				std::vector<Object> m_objects;
				Object* m_object;
				Graphics::Shader* m_shader;
				std::vector<float3> makeVertices();
				SkyboxType m_type = SkyboxType::STATIC;
				sPoint<Graphics::Image> m_image;
				sPoint<Graphics::Image> m_image2;
				float m_blendFactor = 0.5f;
				float m_cycleTime = 60.0f;
				float m_tenPercent = m_cycleTime / 10.f;
				float m_half = m_cycleTime / 2.0f;
				Timer m_timer;

				GLint m_TIDs[2] = { 0, 1 };

			public:
				Skybox(const sPoint<Graphics::Image>& image);
				Skybox(const sPoint<Graphics::Image>& image, const sPoint<Graphics::Image>& image2);
				void render(const matrix4x4& projection, const matrix4x4& view);	
				inline void cycleTime(const float& time) { m_cycleTime = time; }

			private:
				void cycle();
		};
	}
}
