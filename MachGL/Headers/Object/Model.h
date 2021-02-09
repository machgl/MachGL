/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../../Headers/Core/Includes.h"
#include "../../Headers/Core/DataStructures.h"

namespace MachGL {
	namespace Object {

		class Model {

			private:
				std::string m_filepath;
				std::vector<float3> m_vertices;
				std::vector<float3> m_normals;
				std::vector<float2> m_vertexTextures;
				std::vector<float3> m_vertexNormals;
				std::vector<float2> m_UVs;
				std::vector<GLushort> m_indices;
				void load();
				void tokenise(std::string const& str, const char& delim, std::vector<std::string>& out);
				bool m_hasTexture = true;
			public:
				Model() = default;
				Model(const std::string& filepath);
				Model(const std::vector<float3>& vertices);
				Model(const std::vector<float3>& vertices, const std::vector<float3>& normals, const std::vector<float2>& UVs, 
					const std::vector<GLushort>& indices);

				inline const std::vector<float3>& getVertices() const { return m_vertices; }
				inline const std::vector<GLushort>& getIndices() const { return m_indices; }
				inline const std::vector<float3>& getNormals() const { return m_vertexNormals; }
				inline const std::vector<float2>& getUVs() const { return m_vertexTextures; }

				inline const int& getVertexSize() const { return m_vertices.size(); }
				inline const int& getIndexSize() const { return m_indices.size(); }
				inline sPoint<Model> ref() { return make_sPoint<Model>(*this); }
			};
		
	}
}