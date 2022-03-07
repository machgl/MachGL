/*

	MachGL (Alpha)

 */

#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"
#include "AudioFile.h"

namespace MachGL {
	namespace Audio {
	
		enum class AudioFileFormats {

			OGG, MP3, UNKNOWN
		};

		class SoundBuffer {

			protected:
				std::vector<AudioFile> m_soundEffects;

			public:
				static sPoint<SoundBuffer> createSoundBuffer();
				SoundBuffer() = default;
				~SoundBuffer() = default;
				virtual void addSoundEffect(AudioFile& audioFile) = 0;
				virtual void removeSoundEffect(AudioFile& audioFile) = 0;
		};

		using MACH_SOUND_BUFFER = sPoint<SoundBuffer>;
	}
}