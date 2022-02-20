/*
 
    MachGL (Alpha)
 
 */

#include "../../../Headers/API/OpenGL/OpenGLRenderer2D.h"

namespace MachGL {
    namespace Graphics {

        void OpenGLRenderer2D::flush(const Plane::MACH_PLANE& plane) {

            glBindVertexArray(plane->getVAO());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plane->getIBO());

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, plane->getTID());

            glBindTextureUnit(0, plane->getTID());

            glDrawElements(GL_TRIANGLES, (GLsizei)plane->getIndices().size(), GL_UNSIGNED_SHORT, NULL);
            
            glBindTexture(GL_TEXTURE_2D, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
    }
}



