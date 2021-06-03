/*

Mach::GL (Alpha)

*/

#include "../../Headers/Particle/ParticleCluster.h"

namespace MachGL {
	namespace Particle {

		ParticleCluster::ParticleCluster(const ParticleProperties& properties, const uint32_t& particles) 
			: m_properties(properties), m_particles(particles) {

            if (!m_properties.object) MACH_ERROR_MSG("Please define an object for the particle system");
			
            m_renderer = Graphics::Renderer3D::createRenderer();
			m_shader = Graphics::Shader::createShader("CoreAssets/CoreShaders/particle.vert", "CoreAssets/CoreShaders/particle.frag");
			m_particle = CubeParticle();
		}

		void ParticleCluster::render() {

			m_shader->enable();
			//m_renderer->submit(m_objects);
			m_shader->disable();
		}

		void ParticleCluster::update() {

		}
	}
}
