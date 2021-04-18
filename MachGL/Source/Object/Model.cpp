/*

Mach::GL (Alpha)

*/

#include "../../Headers/Object/Model.h"
#include "../../Headers/Maths/Vector.h"
#include "../../Headers/Utilities/FileUtilities.h"

namespace MachGL {
	namespace Object {

        Model::Model(const std::string& filepath)
			: m_filepath(filepath) {

			load();
		}

        Model::Model(const std::vector<float3>& vertices) : m_vertices(vertices) { }

        Model::Model(const std::vector<float3>& vertices, const std::vector<float3>& normals, const std::vector<float2>& UVs, 
            const std::vector<GLushort>& indices)
            : m_vertices(vertices), m_vertexNormals(normals), m_vertexTextures(UVs), m_indices(indices) { }
		
        void Model::load() {

            std::ifstream file(m_filepath);
            bool firstFace = true;

            if (!file.is_open()) {

                MACH_ERROR_MSG("Could not load: " + m_filepath);
                return;
            }

            while (!file.eof()) {

                char line[128];
                file.getline(line, 128);
                std::strstream s;
                s << line;
                char junk;

                if (line[0] == 'v') {

                    if (line[1] == 'n') {

                        float3 vn;
                        s >> junk >> junk >> vn.x >> vn.y >> vn.z;
                        m_normals.push_back(vn);

                    }
                    if (line[1] == 't') {

                        float2 vt;
                        s >> junk >> junk >> vt.x >> vt.y;
                        m_UVs.push_back(vt);
                    }
                    else {

                        float3 v;
                        s >> junk >> v.x >> v.y >> v.z;
                        m_vertices.push_back(v);
                    }
                }
            
                if (line[0] == 'f') {
                    if (firstFace) {

                        if (m_UVs.size() < 1) m_hasTexture = false;
                        if (m_hasTexture) m_vertexTextures = std::vector<float2>(m_vertices.size());
                        m_vertexNormals = std::vector<float3>(m_vertices.size());
                        firstFace = false;
                    }

                    std::string faces[3];
                    s >> junk >> faces[0] >> faces[1] >> faces[2];

                    for (uint32_t i = 0; i < 3; i++) {

                        std::vector<std::string> face;
                        Utilities::tokenize(faces[i], (char)12079, face);

                        if (m_hasTexture) {

                            m_vertexTextures[static_cast<uint64_t>(std::stoi(face[0])) - 1] = m_UVs[static_cast<uint64_t>(std::stoi(face[1])) - 1];
                            m_vertexNormals[static_cast<uint64_t>(std::stoi(face[0])) - 1] = m_normals[static_cast<uint64_t>(std::stoi(face[2])) - 1];
                        }
                        else  m_vertexNormals[static_cast<uint64_t>(std::stoi(face[0])) - 1] = m_normals[static_cast<uint64_t>(std::stoi(face[1])) - 1];
                        m_indices.push_back(std::stoi(face[0]) - 1);
                    }
                }
            }

            file.close();
        }
	}
}