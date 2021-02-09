/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../../Headers/Core/Includes.h"
#include "../../Headers/Core/DataStructures.h"
#include "Model.h"
#include "../../Headers/Maths/Vector.h"

namespace MachGL {
	namespace Object {

		class Terrain {

			private:
				sPoint<Model> m_model;
				int m_size;
				int m_vertexCount;
				float m_amplitude;
				int m_octaves;
				float m_roughness;
				long m_seed;
				sPoint<Model> generateTerrain();
				Noise m_noise;
				float generateHeight(const float& x, const float& z);
				float3 calculateNormal(const float&x, const float& z);
			public:
				Terrain() = default;
				Terrain(const int& size, const int& vertexCount);
				Terrain(const int& size, const int& vertexCount, const float& amplitude, 
					const int& octaves, const float& roughness, const int& seed);
				const sPoint<Model>& getModel() const { return m_model; }
		};
	}
}
