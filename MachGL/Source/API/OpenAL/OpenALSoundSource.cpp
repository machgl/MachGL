/*

	Mach::GL (Alpha)
	
*/

#include "../../../Headers/API/OpenAL/OpenALSoundSource.h"

namespace MachGL {
	namespace Audio {

		OpenALSoundSource::OpenALSoundSource() {

			alGenSources(1, &(ALuint)m_source);
			alSourcef((ALuint)m_source, AL_PITCH, m_pitch);
			alSourcef((ALuint)m_source, AL_GAIN, m_gain);
			alSource3f((ALuint)m_source, AL_POSITION, m_position.x, m_position.y, m_position.z);
			alSource3f((ALuint)m_source, AL_VELOCITY, m_velocity.x, m_velocity.y, m_velocity.z);
			alSourcei((ALuint)m_source, AL_LOOPING, m_loop);
			alSourcei((ALuint)m_source, AL_BUFFER, (ALint)m_buffer);
		}

		OpenALSoundSource::~OpenALSoundSource() {
			alDeleteSources(1, &m_source);
		}

		void OpenALSoundSource::play(const uint32_t& buffer) {

			if (buffer != m_buffer) {

				m_buffer = buffer;
				alSourcei((ALuint)m_source, AL_BUFFER, (ALint)buffer);
			}

			alSourcePlay((ALuint)m_source);
		}
	}
}

