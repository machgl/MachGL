/*

Mach::GL (Alpha)

*/

#include "../../Headers/Object/Model.h"

namespace MachGL {
	namespace Object {

		Model::Model(const char* filepath) 
			: m_filepath(filepath) {

			load();
		}

        Model::Model(const std::vector<float3>& vertices) : m_vertices(vertices) { }

        Model::Model(const std::vector<float3>& vertices, const std::vector<float3>& normals, const std::vector<float2>& UVs, 
            const std::vector<GLushort>& indices)
            : m_vertices(vertices), m_vertexNormals(normals), m_vertexTextures(UVs), m_indices(indices) {

        }
		
        void Model::tokenise(std::string const& str, const char& delim, std::vector<std::string>& out) {

            size_t start;
            size_t end = 0;

            while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {

                end = str.find(delim, start);
                out.push_back(str.substr(start, end - start));
            }
        }

        void Model::load() {

            std::ifstream file(m_filepath);

            if (!file.is_open()) {

                std::cout << "Could not load: " << m_filepath << std::endl;
                return;
            }

            int vtCount = 0;

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

                    if (m_vertices.size() != m_UVs.size() && m_UVs.size() > 0)
                        m_vertices.resize(m_UVs.size());

                    if (m_UVs.size() < 1) m_hasTexture = false;

                    if (m_hasTexture)
                        m_vertexTextures = std::vector<float2>(m_UVs.size());

                    m_vertexNormals = std::vector<float3>(m_vertices.size());
                    break;
                }
            }

            file.close();

            std::ifstream readFile(m_filepath);

            while (!readFile.eof()) {

                char line[128];
                readFile.getline(line, 128);
                std::strstream s;
                s << line;
                char junk;

                if (line[0] == 'f') {

                    GLushort f[3];
                    GLushort ti[3];
                    GLushort ni[3];

                    std::vector<std::string> face1, face2, face3;
                    std::string f1, f2, f3;

                    s >> junk >> f1 >> f2 >> f3;

                    tokenise(f1, (char)12079, face1);
                    tokenise(f2, (char)12079, face2);
                    tokenise(f3, (char)12079, face3);

                    f[0] = std::stoi(face1[0]);
                    f[1] = std::stoi(face2[0]);
                    f[2] = std::stoi(face3[0]);

                    if (m_hasTexture) {

                        ti[0] = std::stoi(face1[1]);
                        ti[1] = std::stoi(face2[1]);
                        ti[2] = std::stoi(face3[1]);

                        ni[0] = std::stoi(face1[2]);
                        ni[1] = std::stoi(face2[2]);
                        ni[2] = std::stoi(face3[2]);

                        m_vertexTextures[f[0] - 1] = m_UVs[ti[0] - 1];
                        m_vertexTextures[f[1] - 1] = m_UVs[ti[1] - 1];
                        m_vertexTextures[f[2] - 1] = m_UVs[ti[2] - 1];
                    }
                    else {

                        ni[0] = std::stoi(face1[1]);
                        ni[1] = std::stoi(face2[1]);
                        ni[2] = std::stoi(face3[1]);
                    }

                    m_vertexNormals[f[0] - 1] = m_normals[ni[0] - 1];
                    m_vertexNormals[f[1] - 1] = m_normals[ni[1] - 1];
                    m_vertexNormals[f[2] - 1] = m_normals[ni[2] - 1];

                    for (int i = 0; i < 3; i++) {

                        m_indices.push_back(f[i] - 1);
                    }
                }
            }

            readFile.close();
        }
	}
}