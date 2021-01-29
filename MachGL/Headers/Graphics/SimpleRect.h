/*

Mach::Gl (Alpha)

*/

#pragma once

#include "../../Headers/Core/Includes.h"
#include "../../Headers/Core/DataStructures.h"
#include "Image.h"
#include "Shader.h"
#include "Plane.h"
#include "../../Headers/Maths/Matrix.h"
#include "Renderer2D.h"

namespace MachGL {
	namespace Graphics {

		class SimpleRect : public Plane {

			private:
				float2 m_pos;
				float2 m_size;
				float4 m_color = float4(1.0f, 1.0f, 1.0f, 1.0f);
				Image* m_image;
				matrix4x4 m_projection;
<<<<<<< HEAD
				std::unique_ptr<Shader> m_shader;
=======
				Shader* m_shader;
				Plane* m_plane;
>>>>>>> parent of 7a8f169... Smart Pointers
				float m_windowWidth;
				float m_windowHeight;
				Renderer2D* m_renderer;
				GLint m_TIDs[32] = { 
					0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
					16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 
				};
				float m_alpha = 1.0f;
				
			public:
				SimpleRect(const float2& pos, const float2& size, Image* image, const float& windowWidth, const float& windowHeight);
				SimpleRect(const float2& pos, const float2& size, const float4& color, const float& windowWidth, const float& windowHeight);
				void render();
				~SimpleRect();

				inline void setAlpha(const float& alpha) { m_alpha = alpha; }
		};
	}
}
