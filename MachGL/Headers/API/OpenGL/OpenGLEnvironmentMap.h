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
				void reflectedObjects(const std::vector<Object::MACH_OBJECT>& objects, const Object::Camera& camera) override;
				void reflectedObjects(const std::vector<Object::MACH_OBJECT>& objects, const Object::Camera& camera, const Object::MACH_SKYBOX& skybox) override;
			protected:
				void init() override;
		};
	}
}
