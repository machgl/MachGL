/*

Mach::GL (Alpha)

*/

#include "../../Headers/Plane/SimpleTriangle.h"

namespace MachGL {
	namespace Plane {

		SimpleTriangle::SimpleTriangle(const float2& position, const float2& size, const Graphics::MACH_IMAGE& image, const WindowDimension& windowDimension)
			: m_position(position), m_size(size), m_image(image), m_windowDimension(windowDimension) {

            m_renderer = Graphics::Renderer2D::createRenderer();
			m_projection = Maths::Matrix::simpleOrthographic(m_windowDimension);
			m_shader = Graphics::Shader::createShader("../MachGL/CoreAssets/CoreShaders/simple.mglsdr");
			m_UBO = Graphics::UniformBuffer::createUniformBuffer(sizeof(matrix4x4), 3);
			m_UBO->configureUBO(m_shader, "SimpleMatrices");

			PlaneProperties planeProperties;
			planeProperties.position = float3(m_position, 0);
			planeProperties.size = m_size;
			planeProperties.image = m_image;
			planeProperties.shape = PlaneShape::TRIANGLE;

			m_plane = Plane::Plane::createPlane(planeProperties);
            m_plane->create();
			m_planes.push_back(m_plane);

			m_UBO->pushToBuffer(m_projection);
		}

		SimpleTriangle::SimpleTriangle(const float2& position, const float2& size, const float4& color, const WindowDimension& windowDimension)
			: m_position(position), m_size(size), m_color(color), m_windowDimension(windowDimension) {

            m_renderer = Graphics::Renderer2D::createRenderer();
			m_projection = Maths::Matrix::simpleOrthographic(m_windowDimension);
			m_shader = Graphics::Shader::createShader("../MachGL/CoreAssets/CoreShaders/simple.mglsdr");
			m_UBO = Graphics::UniformBuffer::createUniformBuffer(sizeof(matrix4x4), 3);
			m_UBO->configureUBO(m_shader, "SimpleMatrices");

			PlaneProperties planeProperties;
			planeProperties.position = float3(m_position, 0);
			planeProperties.size = m_size;
			planeProperties.image = m_image;
			planeProperties.shape = PlaneShape::TRIANGLE;

			m_plane = Plane::Plane::createPlane(planeProperties);
            m_plane->create();
			m_planes.push_back(m_plane);

			m_UBO->pushToBuffer(m_projection);
		}

		void SimpleTriangle::render() {
		
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			m_shader->enable();
			m_shader->setUniform1f("_simple_alpha", m_alpha);
			m_renderer->submit(m_planes);
			m_shader->disable();

			glDisable(GL_BLEND);
		}
	}
}
