/*

	Mach::GL (Alpha)

*/

#pragma once

#include "../../Audio/SoundSource.h"

namespace MachGL {
	namespace Audio {

		class OpenALSoundSource : public SoundSource {

			public:
				OpenALSoundSource(const SoundSourceProperties& properties);
				~OpenALSoundSource();
				void play(const uint32_t& buffer) override;
				void setPitch(const float& pitch) override;
				void setGain(const float& gain) override;
				void setPosition(const float3& position) override;
				void setVelocity(const float3& velocity) override;
				void setLoop(const bool& loop) override;
		};
	}
}