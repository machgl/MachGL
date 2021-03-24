/*

Mach::GL (Alpha)

*/

#include "../../Headers/Scene/Scene.h"

namespace MachGL {
	namespace Scene {

		Scene::Scene(const std::string& filepath) : m_filepath(filepath) {
			loadScene(m_filepath);
		}

		void Scene::loadScene(const std::string& filepath) {

			if (filepath.substr(filepath.find_last_of(".") + 1) != "msf") {
				
				MACH_ERROR_MSG("File type not a MachGL scene file (.msf)");
				return;
			}

			//Load scene here 
		}

		void Scene::renderScene() {

			m_renderer.submit(m_objects);
		}
	}
}
