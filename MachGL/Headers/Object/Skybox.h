/*

Mach::GL (Alpha) 


*/

#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"
#include "../Graphics/Image.h"
#include "Model.h"
#include "Object.h"
#include "../Graphics/Renderer3D.h"
#include "../Graphics/Shader.h"

namespace MachGL {
	namespace Object {

		enum class SkyboxType {

			STATIC, DYNAMIC
		};

		class Skybox {

			private:
				std::vector<float3>         m_vertices;
				Graphics::MACH_RENDERER_3D  m_renderer;
				std::vector<MACH_OBJECT>    m_objects;
				MACH_OBJECT      		    m_object;
				Graphics::MACH_SHADER       m_shader;
				SkyboxType				    m_type		  = SkyboxType::STATIC;
				Graphics::MACH_IMAGE	    m_image;
				Graphics::MACH_IMAGE        m_image2;
				float					    m_blendFactor = 0.5f;
				float					    m_cycleTime   = 60.0f;
				float					    m_tenPercent  = m_cycleTime / 10.f;
				float					    m_half        = m_cycleTime / 2.0f;
				Timer					    m_timer;

			public:

				static sPoint<Skybox> createSkybox(const Graphics::MACH_IMAGE& image);
				static sPoint<Skybox> createSkybox(const Graphics::MACH_IMAGE& image, const Graphics::MACH_IMAGE& image2);
				static sPoint<Skybox> createSkybox(const GLuint& cubemapID);

				Skybox() = default;
				~Skybox() = default;
				Skybox(const Graphics::MACH_IMAGE& image);
				Skybox(const Graphics::MACH_IMAGE& image, const Graphics::MACH_IMAGE& image2);
				Skybox(const GLuint& cubemapID);
				void render(const matrix4x4& projection, const matrix4x4& view);	
				inline void cycleTime(const float& time) { m_cycleTime = time; }
				inline const GLuint& getTexture() const { return m_image->getTID(); }
				inline const auto& getObject() const { return m_object; }
				inline auto ref() { return make_sPoint<Skybox>(*this); }

			private:
				void cycle();
				std::vector<float3>	makeVertices();
		};

		using MACH_SKYBOX = sPoint<Skybox>;
	}
}
