/*

Mach::GL (Alpha) 


*/

#pragma once

#include "../../Graphics/EnvironmentMap.h"

namespace MachGL {
	namespace Graphics {

		class OpenGLEnvironmentMap : public EnvironmentMap {

			public:
				OpenGLEnvironmentMap(const float& size, const WindowDimension& windowDimension);
				void capture() override;
				void stop() override;
				void init() override;
			private:
				void renderFace(const std::vector<Object::MACH_OBJECT>& objects, const Object::Camera& camera, const uint32_t& face) override;
		};
	}
}
