/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"
#include "../Object/Object.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Renderer3D.h"
#include "CubeParticle.h"

namespace MachGL {
	namespace Particle {

		enum class ParticleType {

			CUBE, QUAD
		};

		struct ParticleProperties {

			float3					position  = float3(0);
			float3					scale     = float3(1.0f);
			float4					color	  = float4(1);
			Object::MACH_OBJECT     object;
			float					velocity  = 1.0f;
			float3					direction = float3(0, 1, 0);
		};

		class ParticleCluster {

			private:
				bool						      m_active		= false;
				bool						      m_defaultShader = true;
				ParticleProperties			      m_properties;
				Graphics::MACH_SHADER	          m_shader;
				Graphics::MACH_RENDERER_3D        m_renderer;
				uint32_t					      m_particles;
				std::vector<Object::MACH_OBJECT> m_objects;
				Particle					      m_particle;

			public:
				ParticleCluster(const ParticleProperties& properties, const uint32_t& particles);
				~ParticleCluster() = default;
				void render();
				void update();
				inline void activate() { m_active = true; }
		};
	}
}
