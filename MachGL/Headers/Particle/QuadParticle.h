/*

Mach::GL (Alpha) 


*/

#pragma once

#include "Particle.h"
#include "../Plane/Plane.h"

namespace MachGL {
	namespace Particle {

		class QuadParticle : public Particle {

			private:
				Plane::Plane		   m_plane;
				Plane::PlaneProperties m_planeProperties;

			public:
				QuadParticle(const float3& position, const float4& color);
		};
	}
}
