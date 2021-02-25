#include "../../Headers/Graphics/Renderer3D.h"

namespace MachGL {
    namespace Graphics {

        typedef Object::ObjectType type;

        void Renderer3D::submit(const std::vector<Object::Object>& objects) {

            for (uint32_t i = 0; i < objects.size(); i++) {

                flush(objects[i]);
            }
        }

        void Renderer3D::submit(const std::vector<Object::Object>& objects, const Object::Camera& camera, const float& renderDistance) {

            for (uint32_t i = 0; i < objects.size(); i++) {
                
                if (objects[i].getType() != type::TERRAIN) {
                    if (Maths::Vector::distance(camera.getPosition(), objects[i].getPosition()) <= renderDistance)
                        flush(objects[i]);
                }
                else flush(objects[i]);
            }
        }

        void Renderer3D::flush(const Object::Object& object) {

            glBindVertexArray(object.getVAO());
            
            if (object.getType() == type::MESH || object.getType() == type::TERRAIN) {

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.getIBO());
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
                glFrontFace(GL_CCW);

                glActiveTexture(GL_TEXTURE0 + object.getTID());
                glBindTexture(GL_TEXTURE_2D, object.getTID());
            }

            if (object.getType() == type::MESH || object.getType() == type::TERRAIN)
                glDrawElements(GL_TRIANGLES, (GLsizei)object.getModel()->getIndexSize(), GL_UNSIGNED_SHORT, NULL);

            if (object.getType() == type::SKYBOX) {

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_CUBE_MAP, object.getTID());
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_CUBE_MAP, object.getTID2());
                glDrawArrays(GL_TRIANGLES, 0, (GLsizei)object.getModel()->getVertices().size());
            }

            if (object.getType() == type::MESH || object.getType() == type::TERRAIN) {

                glDisable(GL_CULL_FACE);
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            if (object.getType() == type::MESH || object.getType() == type::TERRAIN)
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            glBindVertexArray(0);
        }
    }
}