/*

Mach::GL (Alpha) 


*/

#pragma once

#include "Includes.h"
#include "DataStructures.h"
#include "Model.h"

namespace MachGL {
	namespace Object {

		class Terrain {

			private:
				Model* m_model;
				int m_size;
				int m_vertexCount;
				Model* generateTerrain();
				float generateHeight(const float& x, const float& z);
				float3 calculateNormal(const float&x, const float& z);
			public:
				Terrain(int size, int vertexCount);
				Model* getModel() const { return m_model; }
		};
	}
}
