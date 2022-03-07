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
			inline static void setGraphicsAPI(const API& graphicsAPI) { s_graphicsAPI = graphicsAPI; }
	};

	class AudioAPI {

		public:
			enum class API {

				MACH_OPEN_AL
			};

		private:
			static API s_audioAPI;

		public:
			inline static API getAudioAPI() { return s_audioAPI; }
			inline static void setAudioAPI(const API& audioAPI) { s_audioAPI = audioAPI; }
	};
}
