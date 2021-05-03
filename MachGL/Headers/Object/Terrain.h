/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"
#include "Model.h"
#include "../Maths/Vector.h"

namespace MachGL {
	namespace Object {

		class Terrain {

			private:
				sPoint<Model> m_model;
				uint32_t      m_size;
				uint32_t	  m_vertexCount;
				float	      m_amplitude;
				uint32_t      m_octaves;
				float         m_roughness;
				long          m_seed;
				Noise         m_noise;

			public:
				Terrain() = default;
				Terrain(const uint32_t& size, const uint32_t& vertexCount);
				Terrain(const uint32_t& size, const uint32_t& vertexCount, const float& amplitude,
					const uint32_t& octaves, const float& roughness, const long& seed);
				const sPoint<Model>& getModel() const { return m_model; }
			
			private:
				float generateHeight(const float& x, const float& z);
				float3 calculateNormal(const float&x, const float& z);
				sPoint<Model> generateTerrain();
		};
	}
}
