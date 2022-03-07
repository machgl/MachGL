/*

	Mach::GL (Alpha)

*/

#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"

namespace MachGL {
	namespace Audio {

		class SoundSource {

			protected:
				uint32_t m_source = 0;
				uint32_t m_buffer = 0;
				float m_pitch = 1.0f;
				float m_gain = 1.0f;
				float3 m_position = float3(0);
				float3 m_velocity = float3(0);
				bool m_loop = false;

			public:
				static sPoint<SoundSource> createSoundSource();
				SoundSource() = default;
				~SoundSource() = default;

				virtual void play(const uint32_t& buffer) = 0;
		};

		using MACH_SOUND_SOURCE = sPoint<SoundSource>;
	}
}
