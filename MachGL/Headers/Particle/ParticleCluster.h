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

		struct ParticleProperties {

			float3 position = float3(0);
			float3 scale = float3(1.0f);
			float4 color = float4(1);
			sPoint<Object::Object> object;
			float velocity = 1.0f;
			float3 direction = float3(0, 1, 0);
		};

		class ParticleCluster {

			private:
				bool m_active = false;
				bool m_defaultShader = true;
				ParticleProperties m_properties;
				uPoint<Graphics::Shader> m_shader;
				Graphics::Renderer3D m_renderer;
				uint32_t m_particles;
				std::vector<Object::Object> m_objects;
				Particle m_particle;

			public:
				ParticleCluster(const ParticleProperties& properties, const uint32_t& particles);
				~ParticleCluster() = default;
				void render();
				void update();
				inline void activate() { m_active = true; }
		};
	}
}
