/*

	MachGL (Alpha)

 */

#pragma once

#include "MachPCH.h"
#include "../../Audio/SoundBuffer.h"

namespace MachGL {
	namespace Audio {

		class OpenALSoundBuffer : public SoundBuffer {

			public:
				OpenALSoundBuffer() = default;
				~OpenALSoundBuffer();
				void addSoundEffect(AudioFile& audioFile) override;
				void removeSoundEffect(AudioFile& audioFile) override;

			private:
				AudioFileFormats getFormat(const std::string& filename);
				ALenum getALFormat(uint32_t channels);
				ALuint loadOggFromFile(const std::string& filename);
				ALuint loadMP3FromFile(const std::string& filename);
				const std::string& getVorbisError(const int& errorCode);
		};
	}
}