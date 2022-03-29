/*

	Mach::GL (Alpha)

*/

#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"

namespace MachGL {
	namespace Audio {

		struct SoundSourceProperties {

			float pitch = 1.0f;
			float gain = 1.0f;
			float3 position = float3(0);
			float3 velocity = float3(0);
			bool loop = false;
		};

		class SoundSource {

			protected:
				uint32_t m_source = 0;
				uint32_t m_buffer = 0;
				SoundSourceProperties m_properties;

			public:
				static sPoint<SoundSource> createSoundSource(const SoundSourceProperties& properties);
				SoundSource() = default;
				~SoundSource() = default;

				virtual void play(const uint32_t& buffer) = 0;
				virtual void setPitch(const float& buffer) = 0;
				virtual void setGain(const float& gain) = 0;
				virtual void setPosition(const float3& position) = 0;
				virtual void setVelocity(const float3& velocity) = 0;
				virtual void setLoop(const bool& loop) = 0;
		};

		using MACH_SOUND_SOURCE = sPoint<SoundSource>;
	}
}
