/*

	Mach::GL (Alpha)

*/

#pragma once

#include "../../Audio/SoundSource.h"

namespace MachGL {
	namespace Audio {

		class OpenALSoundSource : public SoundSource {

			public:
				OpenALSoundSource();
				~OpenALSoundSource();
				void play(const uint32_t& buffer) override;
		};
	}
}