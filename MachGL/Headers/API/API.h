/*

Mach::GL (Alpha) 


*/

#pragma once

namespace MachGL {

	class GraphicsAPI {

		public:
			enum class API {

				MACH_OPEN_GL, MACH_VULKAN
			};

		private:
			static API s_graphicsAPI;

		public:
			inline static API getGraphicsAPI() { return s_graphicsAPI; }
			inline static void setGraphicsAPI(API graphicsAPI) { s_graphicsAPI = graphicsAPI; }
	};
}
