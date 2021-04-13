/*

Mach::GL (Alpha)

*/

#include "../../Headers/Particle/ParticleCluster.h"

namespace MachGL {
	namespace Particle {

		ParticleCluster::ParticleCluster(const ParticleProperties& properties, const uint32_t& particles) 
			: m_properties(properties), m_particles(particles) {

			if (!m_properties.object) std::cout << "ERROR: Please define an object for the particle system" << std::endl;
			
			m_shader = make_uPoint<Graphics::Shader>("CoreAssets/CoreShaders/particle.vert", "CoreAssets/CoreShaders/particle.frag");
			m_particle = CubeParticle();
		}

		void ParticleCluster::render() {

			m_shader->enable();
			m_renderer.submit(m_objects);
			m_shader->disable();
		}

		void ParticleCluster::update() {

		}
	}
}
