#include "../../Headers/Graphics/Renderer2D.h"

namespace MachGL {
	namespace Graphics {

        void Renderer2D::submit(const std::vector<Plane::Plane>& planes) {

            for (uint32_t i = 0; i < planes.size(); i++) {

                flush(planes[i]);
            }
        }

        void Renderer2D::submit(const Plane::Plane& plane) { flush(plane); }

        void Renderer2D::flush(const Plane::Plane& plane) {

            glBindVertexArray(plane.getVAO());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plane.getIBO());

            glActiveTexture(GL_TEXTURE0 + plane.getTID());
            glBindTexture(GL_TEXTURE_2D, plane.getTID());

            glDrawElements(GL_TRIANGLES, (GLsizei)plane.getIndices().size(), GL_UNSIGNED_SHORT, NULL);
            
            glBindTexture(GL_TEXTURE_2D, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
	}
}