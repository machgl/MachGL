/*

Mach::GL (Alpha) 


*/

#pragma once

#define FAST_OBJ_IMPLEMENTATION

#include "MachPCH.h"
#include "../Core/DataStructures.h"

namespace MachGL {
	namespace Object {

		enum class ModelType { MESH, SKYBOX, TERRAIN };

		class Model {

			private:
				std::string			      m_filepath;
				std::vector<float3>       m_vertices;
				std::vector<float3>       m_normals;
				std::vector<float2>       m_vertexTextures;
				std::vector<float3>       m_vertexNormals;
				std::vector<float2>       m_UVs;
				std::vector<unsigned int> m_indices;
				bool				      m_hasTexture   = true;
				
			public:
                Model() = default;
				Model(const std::string& filepath);
				Model(const std::vector<float3>& vertices);
				Model(const std::vector<float3>& vertices, const std::vector<float3>& normals, const std::vector<float2>& UVs, 
					const std::vector<unsigned int>& indices);

				inline const std::vector<float3>& getVertices() const { return m_vertices; }
				inline const std::vector<unsigned int>& getIndices() const { return m_indices; }
				inline const std::vector<float3>& getNormals() const { return m_vertexNormals; }
				inline const std::vector<float2>& getUVs() const { return m_vertexTextures; }
				inline const bool hasTexture() const { return m_hasTexture; }

				inline const size_t getVertexSize() const { return m_vertices.size(); }
				inline const size_t getIndexSize() const { return m_indices.size(); }
				inline sPoint<Model> ref() { return make_sPoint<Model>(*this); }

				static sPoint<Model> createModel(const std::string& filepath);
				static sPoint<Model> createModel(const std::vector<float3>& vertices);
				static sPoint<Model> createModel(const std::vector<float3>& vertices, const std::vector<float3>& normals, const std::vector<float2>& UVs,
					const std::vector<unsigned int>& indices);
                
			private:
				void load();
        };
        
        using MACH_MODEL = sPoint<Model>;
	}
}
