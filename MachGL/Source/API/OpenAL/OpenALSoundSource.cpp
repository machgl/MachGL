/*

	Mach::GL (Alpha)
	
*/

#include "../../../Headers/API/OpenAL/OpenALSoundSource.h"

namespace MachGL {
	namespace Audio {

		OpenALSoundSource::OpenALSoundSource(const SoundSourceProperties& properties) {

			m_properties = properties;

			alGenSources(1, &(ALuint)m_source);

			setPitch(m_properties.pitch);
			setGain(m_properties.gain);
			setPosition(m_properties.position);
			setVelocity(m_properties.velocity);
			setLoop(m_properties.loop);

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

		void OpenALSoundSource::setPitch(const float& pitch) {

			alSourcef((ALuint)m_source, AL_PITCH, pitch);
		}

		void OpenALSoundSource::setGain(const float& gain) {

			alSourcef((ALuint)m_source, AL_GAIN, gain);
		}

		void OpenALSoundSource::setPosition(const float3& position) {

			alSourcefv((ALuint)m_source, AL_POSITION, &m_properties.position[0]);
		}

		void OpenALSoundSource::setVelocity(const float3& velocity) {

			alSourcefv((ALuint)m_source, AL_VELOCITY, &m_properties.velocity[0]);
		}

		void OpenALSoundSource::setLoop(const bool& loop) {

			alSourcei((ALuint)m_source, AL_LOOPING, loop);
		}
	}
}

