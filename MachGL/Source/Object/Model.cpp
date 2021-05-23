/*

Mach::GL (Alpha)

*/

#include "../../Headers/Object/Model.h"
#include "../../Headers/Maths/Vector.h"
#include "../../Headers/Utilities/FileUtilities.h"

namespace MachGL {
	namespace Object {

        Model::Model(const std::string& filepath) : m_filepath(filepath) { 
            
            load(); 
        }

        Model::Model(const std::vector<float3>& vertices) : m_vertices(vertices) {
        
        }

        Model::Model(const std::vector<float3>& vertices, const std::vector<float3>& normals, const std::vector<float2>& UVs, 
            const std::vector<unsigned int>& indices)
            : m_vertices(vertices), m_vertexNormals(normals), m_vertexTextures(UVs), m_indices(indices) { 
        
        }
		
        void Model::load() {

            auto* mesh = fast_obj_read(m_filepath.c_str());
            
            if (!mesh) {

                MACH_ERROR_MSG("Could not load: " + m_filepath);
                return;
            }

            m_indices = std::vector<unsigned int>((uint64_t)mesh->face_count * 3);
          
            for (uint32_t i = 0; i < mesh->group_count; i++) {

                auto& group = mesh->groups[i];
                uint32_t   index = 0;
                
                for (uint32_t j = 0; j < group.face_count; j++) {

                    uint32_t face_vertices = mesh->face_vertices[group.face_offset + j];

                    for (uint32_t k = 0; k < face_vertices; k++) {

                        auto mesh_index = mesh->indices[group.index_offset + index];

                        m_vertices.push_back(float3(mesh->positions[3 * mesh_index.p + 0],
                                                    mesh->positions[3 * mesh_index.p + 1],
                                                    mesh->positions[3 * mesh_index.p + 2]));

                        m_vertexNormals.push_back(float3(mesh->normals[3 * mesh_index.n + 0],
                                                         mesh->normals[3 * mesh_index.n + 1],
                                                         mesh->normals[3 * mesh_index.n + 2]));

                        m_vertexTextures.push_back(float2(mesh->texcoords[2 * mesh_index.t + 0],
                                                          mesh->texcoords[2 * mesh_index.t + 1]));

                        m_indices.push_back(index);
                        index++;
                    }
                }
            }

            if (m_vertexTextures.size() > 0) m_hasTexture = true;

            fast_obj_destroy(mesh);
            MACH_MSG("Loaded: " + m_filepath);
        }
	}
}