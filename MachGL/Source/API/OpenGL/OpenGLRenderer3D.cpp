/*
 
    MachGL (Alpha)
 
 */

#include "../../../Headers/API/OpenGL/OpenGLRenderer3D.h"

namespace MachGL {
    namespace Graphics {
    
        void OpenGLRenderer3D::flush(const Object::MACH_OBJECT &object) {
            
            glBindVertexArray(object->getVAO());
            
            if (object->getType() == Object::ObjectType::MESH || object->getType() == Object::ObjectType::TERRAIN) {

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->getIBO());
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
                glFrontFace(GL_CCW);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, object->getTID());
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_CUBE_MAP, object->getEnvironmentMap());
                glDrawElements(GL_TRIANGLES, (GLsizei)object->getModel()->getIndexSize(), GL_UNSIGNED_SHORT, NULL);
                glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
                glDisable(GL_CULL_FACE);
                glBindTexture(GL_TEXTURE_2D, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }

            if (object->getType() == Object::ObjectType::SKYBOX) {

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_CUBE_MAP, object->getTID());
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_CUBE_MAP, object->getTID2());
                glDrawArrays(GL_TRIANGLES, 0, (GLsizei)object->getModel()->getVertices().size());
                glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
            }

            glBindVertexArray(0);
        }
    }
}
