/*

Mach::GL (Alpha) 


*/

#pragma once

#include "Particle.h"

namespace MachGL {
	namespace Particle {

		class CubeParticle : public Particle {

			public:
				CubeParticle() {

					m_vertices = {

						float3(-1, -1, 1),
						float3(-1, 1, 1),
						float3(-1, -1, -1),
						float3(-1, 1, -1),
						float3(1, -1, 1),
						float3(1 ,1, 1),
						 
						float3(1, -1, -1),
						float3(1, 1, -1),
						float3(-1, -1, -1),
						float3(-1, -1, -1),
						float3(-1, -1, 1),
						float3(-1, -1, 1),

						float3(-1, 1, 1),
						float3(-1, 1, 1),
						float3(-1, 1, -1),
						float3(-1, 1, -1),
						float3(1, -1, -1),
						float3(1, -1, -1),

						float3(1, 1, -1),
						float3(1, 1, -1),
						float3(1, -1, 1),
						float3(1, -1, 1),
						float3(1, 1, 1),
						float3(1, 1, 1)
					};

					m_indices = {

						13, 9, 11, 
						16, 17, 10, 
						20, 21, 18,
						24, 12, 22,
						7, 1, 3,
						4, 6, 8,
						13, 15, 9,
						16, 19, 17,
						20, 23, 21,
						24, 14, 12,
						7, 5, 1,
						4, 2, 6
					};

					m_normals = {

						float3(-1, 0, 0), float3(-1, 0, 0), float3(-1, 0, 0),
						float3(0, 0, -1), float3(0, 0, -1), float3(0, 0, -1),
						float3(1, 0, 0), float3(1, 0, 0), float3(1, 0, 0),
						float3(0, 0, 1), float3(0, 0, 1), float3(0, 0, 1),
						float3(0, -1, 0), float3(0, -1, 0), float3(0, -1, 0),
						float3(0, 1, 0), float3(0, 1, 0), float3(0, 1, 0),
						float3(-1, 0, 0), float3(-1, 0, 0), float3(-1, 0, 0),
						float3(0, 0, -1), float3(0, 0, -1), float3(0, 0, -1),
						float3(1, 0, 0), float3(1, 0, 0), float3(1, 0, 0),
						float3(0, 0, 1), float3(0, 0, 1), float3(0, 0, 1),
						float3(0, -1, 0), float3(0, -1, 0), float3(0, -1, 0),
						float3(0, 1, 0), float3(0, 1, 0), float3(0, 1, 0)
					};
				}
		};
	}
}
