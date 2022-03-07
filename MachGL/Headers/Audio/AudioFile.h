/*

	Mach::GL (Alpha)

*/

#pragma once

#include "MachPCH.h"

namespace MachGL {
	namespace Audio {

		class AudioFile {
		
			private:
				uint32_t m_bufferID = 0;
				std::string m_filename;

			public:
				AudioFile(const std::string& filename);
				inline const std::string& const getFilename() { return m_filename; }
				inline void setBufferID(const uint32_t& buffer) { m_bufferID = buffer; }
				inline uint32_t& getBufferID() { return m_bufferID; }
		};
	}
}
